#include "raylib.h"

int main()
{
	int screenWidth = 350;
	int screenHeight = 250;

	int circleRadius = 25;
	int circle_x = screenWidth / 2;
	int circle_y = screenHeight / 2;

	InitWindow(screenWidth, screenHeight, "Axe Game");

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		DrawCircle(circle_x, circle_y, circleRadius, RED);

		if (IsKeyDown(KEY_W) && circle_y > (0+circleRadius)) circle_y -= 1;
		if (IsKeyDown(KEY_S) && circle_y < (screenHeight - circleRadius)) circle_y += 1;
		if (IsKeyDown(KEY_A) && circle_x > (0 + circleRadius)) circle_x -= 1;
		if (IsKeyDown(KEY_D) && circle_x < (screenWidth-circleRadius)) circle_x += 1;

		EndDrawing();
	}
}