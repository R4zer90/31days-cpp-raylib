#include "Player.h"
#include "raylib.h"

Player::Player() {
	x = 20;
	y = 300;
	speed = 200;
	velocityY = 0;
	gravity = 800;
	onGround = false;
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

void Player::Draw() {
	DrawRectangle(x - 20, y - 20, 40, 40, WHITE);
}

void Player::SetOnGround(bool value) {
	onGround = value;
}

void Player::Land(float groundY) {
	y = groundY;
	velocityY = 0;
	onGround = true;
}