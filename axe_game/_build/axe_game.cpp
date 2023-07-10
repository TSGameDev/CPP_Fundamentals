#include "raylib.h"

int main()
{
	int screenWidth = 800;
	int screenHeight = 450;

	int circleRadius = 25;
	int circle_x = screenWidth / 2;
	int circle_y = screenHeight / 2;

	int sqaureWidth = 50;
	int sqaureHeight = 50;
	int sqaure_x = 300;
	int squre_y = 0;

	int movementSpeed = 5;
	int squareMoveDir = 5;

	InitWindow(screenWidth, screenHeight, "Axe Game");

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);
		
		DrawCircle(circle_x, circle_y, circleRadius, BLUE);
		DrawRectangle(sqaure_x, squre_y, sqaureWidth, sqaureHeight, RED);

		squre_y += squareMoveDir;
		if (squre_y > (screenHeight-sqaureHeight) || squre_y < 0) squareMoveDir = -squareMoveDir;

		if (IsKeyDown(KEY_W) && circle_y > (0+circleRadius)) circle_y -= movementSpeed;
		if (IsKeyDown(KEY_S) && circle_y < (screenHeight - circleRadius)) circle_y += movementSpeed;
		if (IsKeyDown(KEY_A) && circle_x > (0 + circleRadius)) circle_x -= movementSpeed;
		if (IsKeyDown(KEY_D) && circle_x < (screenWidth-circleRadius)) circle_x += movementSpeed;

		EndDrawing();
	}
}