#include "raylib.h"
#include "raymath.h"
#include "Character.h"

int main()
{
	//Window Variables
	const int WINDOW_WIDTH = 384;
	const int WINDOW_HEIGHT = 384;
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy Clash");

	//World Variables
	Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{};

	Character knight{};
	knight.setScreenPos(WINDOW_WIDTH, WINDOW_HEIGHT);

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		const float DELTA_TIME = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		//Draw World Map Texture
		mapPos = Vector2Scale(knight.getWorldPos(), -1);
		DrawTextureEx(worldMap, mapPos, 0, 4, WHITE);

		//Update Player Character
		knight.Tick(DELTA_TIME);

		EndDrawing();
	}
	UnloadTexture(worldMap);
	CloseWindow();
}