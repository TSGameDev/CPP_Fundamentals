#include "Character.h"
#include "Enemy.h"
#include "Prop.h"
#include <string>

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

	Enemy goblin{
		Vector2{800.f, 300.f},
		LoadTexture("characters/goblin_idle_spritesheet.png"),
		LoadTexture("characters/goblin_run_spritesheet.png") };

	Enemy slime{
		Vector2{500.f, 700.f},
		LoadTexture("characters/slime_idle_spritesheet.png"),
		LoadTexture("characters/slime_run_spritesheet.png") };

	Enemy* enemies[]{
		&goblin,
		&slime };

	for (auto enemy : enemies)
	{
		enemy->SetTarget(&knight);
	}

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

		if (!knight.GetIsAlive())
		{
			//Not Alive
			DrawText("Game Over!", 55.f, 45.f, 40, RED);
			EndDrawing();
			continue;
		}
		else
		{
			//Alive
			std::string knightsHealth = "Health: ";
			knightsHealth.append(std::to_string(knight.GetHealth()), 0, 5);
			DrawText(knightsHealth.c_str(), 55.f, 45.f, 40, RED);
		}

		//Update Player Character
		knight.Tick(DELTA_TIME);

		for (Enemy* enemy : enemies)
		{
			//Update Enemies
			enemy->Tick(DELTA_TIME);
		}

		//Check for player weapon collisions
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			for (Enemy* enemy : enemies)
			{
				if (CheckCollisionRecs(knight.GetWeaponCollisionRect(), enemy->GetCollisionRect()))
				{
					enemy -> SetIsAlive(false);
				}
			}
		}

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