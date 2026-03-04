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
	if (y > 550) {
		velocityY = 0;
		y = 550;
		onGround = true;
	}
	else {
		onGround = false;
	}
}

int main() {
	InitWindow(800, 600, "Platformer");
	SetTargetFPS(120);
	Player player;
	
	while (!WindowShouldClose()) {
		//Update
		player.Update(GetFrameTime());
		


		//Draw
		BeginDrawing();
		ClearBackground(BLACK);
		player.Draw();
		EndDrawing();
	}
	CloseWindow();
	return 0;
}