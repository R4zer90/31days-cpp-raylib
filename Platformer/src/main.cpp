#include "raylib.h"

class GameObject {
protected:
	float x;
	float y;
public:
	float GetX() const;
	float GetY() const;
};

class Coin : public GameObject {
private:
	bool collected;
public:
	Coin(float startX, float startY);
	void Draw();
	bool IsCollected() const;
	void Collect();
};

class Player : public GameObject {
private:
	float speed;
	float velocityY;
	float gravity;
	bool onGround;
public:
	Player();
	void Update(float dt);
	void Draw();
	void SetOnGround(bool value);
	void Land(float groundY);
};

Coin::Coin(float startX, float startY) {
	x = startX;
	y = startY;
	collected = false;
}

void Coin::Draw() {
	if (!collected) {
		DrawRing(Vector2{ x, y }, 10, 20, 0, 360, 32, GOLD);
	}
}

bool Coin::IsCollected() const {
	return collected;
}

void Coin::Collect() {
	collected = true;
}

Player::Player() {
	x = 20;
	y = 300;
	speed = 200;
	velocityY = 0;
	gravity = 800;
	onGround = false;
}

void Player::Draw() {
	DrawRectangle(x-20, y-20, 40, 40, WHITE);
}

void Player::Land(float groundY) {
	y = groundY;
	velocityY = 0;
	onGround = true;
}

float GameObject::GetX() const {
	return x;
}

float GameObject::GetY() const {
	return y;
}

void Player::SetOnGround(bool value) {
	onGround = value;
}

void Player::Update(float dt) {
	if (IsKeyDown(KEY_LEFT)) {
		x -= speed * dt;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		x += speed * dt;
	}
	if (IsKeyPressed(KEY_SPACE) && onGround) {
		velocityY = -400;
 		onGround = false;
	}
	velocityY += gravity * dt; 
	y += velocityY * dt;
}

int main() {
	InitWindow(800, 600, "Platformer");
	SetTargetFPS(120);
	Player player;
	Coin coin(300,500);
	int score = 0;

	//map logic
	int map[12][16];
	for (int row = 0; row < 12; row++) {
		for (int col = 0; col < 16; col++) {
			map[row][col] = 0;
			if (row == 11) {
				map[row][col] = 1;
			}
		}
	}
	
	while (!WindowShouldClose()) {
		//Update
		player.Update(GetFrameTime());

		float px = player.GetX();
		float py = player.GetY();
		
		Rectangle playerRect{
			px - 20,
			py - 20,
			40,
			40
		};

		if (!coin.IsCollected()) {
			if (CheckCollisionCircleRec(Vector2{ coin.GetX(), coin.GetY() }, 20, playerRect)) {
				coin.Collect();
				score++;
			}
		}

		int colUnder = px / 50;
		int rowUnder = (py + 20) / 50;
		
		if (rowUnder >= 0 && rowUnder < 12 && colUnder >= 0 && colUnder < 16) {
			if (map[rowUnder][colUnder] == 1) {
				float tileTop = rowUnder * 50;
				float groundY = tileTop - 20;
				player.Land(groundY);
			}
			else {
				player.SetOnGround(false);
			}
		}
		else {
			player.SetOnGround(false);
		}
		
		//Draw
		BeginDrawing();
		ClearBackground(BLACK);

		//map
		for (int row = 0; row < 12; row++) {
			for (int col = 0; col < 16; col++) {
				if (map[row][col] == 1) {
					if (row == rowUnder && col == colUnder) {
						DrawRectangle(col * 50, row * 50, 50, 50, GREEN);
					}
					else {
						DrawRectangle(col * 50, row * 50, 50, 50, WHITE);
					}
				}
			}
		}
		DrawText(TextFormat("Score: %d", score), 20, 20, 20, WHITE);
		player.Draw();
		coin.Draw();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}