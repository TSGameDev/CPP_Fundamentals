#include "Character.h"
#include "Prop.h"

int main()
{
	//Window Variables
	const int WINDOW_WIDTH = 384;
	const int WINDOW_HEIGHT = 384;
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Classy Clash");

	//World Variables
	Texture2D worldMap = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
	Vector2 mapPos{};
	const float mapScale{4.0f};

	//Player
	Character knight{ WINDOW_WIDTH, WINDOW_HEIGHT };

	//Props
	const int numberOfProps{ 2 };
	Prop props[numberOfProps]
	{
		Prop{LoadTexture("nature_tileset/Rock.png"), Vector2{600.f, 300.f}},
		Prop{LoadTexture("nature_tileset/Log.png"), Vector2{400.f, 500.f}}
	};

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		const float DELTA_TIME = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		//Draw World Map Texture
		mapPos = Vector2Scale(knight.GetWorldPos(), -1);
		DrawTextureEx(worldMap, mapPos, 0, mapScale, WHITE);

		//Render Props
		for (Prop prop : props)
		{
			prop.Render(knight.GetWorldPos());
		}

		//Update Player Character
		knight.Tick(DELTA_TIME);
		
		//Checking World Boundries
		Vector2 knightWorldPos = knight.GetWorldPos();
		if (knightWorldPos.x < 0.f ||
			knightWorldPos.y < 0.f ||
			knightWorldPos.x + WINDOW_WIDTH > worldMap.width * mapScale ||
			knightWorldPos.y + WINDOW_HEIGHT > worldMap.height * mapScale)
		{
			knight.UndoMovement();
		}

		for (Prop prop : props)
		{
			bool isColliding = CheckCollisionRecs(prop.GetCollisionRect(knight.GetWorldPos()), knight.GetCollisionRect());
			if (isColliding)
				knight.UndoMovement();
		}

		EndDrawing();
	}
	UnloadTexture(worldMap);
	CloseWindow();
}