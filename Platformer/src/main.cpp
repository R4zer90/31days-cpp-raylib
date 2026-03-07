#include "raylib.h"
#include "Player.h"
#include "Coin.h"
#include <vector>

int main() {
	int screenHeight = 600;
	int screenWidth = 800;
	InitWindow(screenWidth, screenHeight, "Platformer");
	SetTargetFPS(120);
	Player player;
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

	//coins
	std::vector<Coin> coins;
	coins.push_back(Coin(100, 500));
	coins.push_back(Coin(200, 400));
	coins.push_back(Coin(300, 500));
	coins.push_back(Coin(500, 400));
	coins.push_back(Coin(600, 500));
	
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

		for (auto& coin : coins){
			if (!coin.IsCollected()) {
				if (CheckCollisionCircleRec(Vector2{ coin.GetX(), coin.GetY() }, 20, playerRect)) {
				coin.Collect();
				score++;
				}
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

		//Map Drawing
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
		for (auto& coin : coins) {
			coin.Draw();
		}
		if (score == coins.size())	{
			int textWidth = MeasureText("LEVEL COMPLETE", 50);
			DrawText("LEVEL COMPLETE", (screenWidth / 2) - (textWidth / 2), (screenHeight / 2) - (50 / 2), 50, WHITE);
		}

		EndDrawing();
	}
	CloseWindow();
	return 0;
}