#include "raylib.h"

class Player {
private:
	float x;
	float y;
	float speed;
	float velocityY;
	float gravity;
	bool onGround;
public:
	Player();
	void Update(float dt);
	void Draw();
	float GetX() const;
	float GetY() const;
	void SetOnGround(bool value);
	void Land(float groundY);
};

Player::Player() {
	x = 400;
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

float Player::GetX() const {
	return x;
}

float Player::GetY() const {
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
		float px = player.GetX();
		float py = player.GetY();
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

		player.Update(GetFrameTime());

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
		player.Draw();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}