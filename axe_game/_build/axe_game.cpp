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

	bool endGameCollision = false;

	InitWindow(screenWidth, screenHeight, "Axe Game");

	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		if (endGameCollision)
		{
			DrawText("GAME OVER!!!", screenWidth / 2, screenHeight / 2, 24, RED);
		}
		else
		{
			//AI squre movement
			squre_y += squareMoveDir;

			//cirlce collision bounds
			int circle_LeftEdge = circle_x - circleRadius;
			int circle_RightEdge = circle_x + circleRadius;
			int circle_TopEdge = circle_y - circleRadius;
			int circle_BottomEdge = circle_y + circleRadius;

			//square collision bounds
			int squre_LeftEdge = sqaure_x;
			int squre_RightEdge = sqaure_x + sqaureWidth;
			int squre_TopEdge = squre_y;
			int squre_BottomEdge = squre_y + sqaureHeight;

			//draw elements
			DrawCircle(circle_x, circle_y, circleRadius, BLUE);
			DrawRectangle(sqaure_x, squre_y, sqaureWidth, sqaureHeight, RED);
			
			//check if squre has hit world bounds, redirect if so.
			if (squre_BottomEdge >= screenHeight || squre_TopEdge <= 0) squareMoveDir = -squareMoveDir;

			//player inputs
			if (IsKeyDown(KEY_W) && circle_TopEdge > 0) circle_y -= movementSpeed;
			if (IsKeyDown(KEY_S) && circle_BottomEdge < screenHeight) circle_y += movementSpeed;
			if (IsKeyDown(KEY_A) && circle_LeftEdge > 0) circle_x -= movementSpeed;
			if (IsKeyDown(KEY_D) && circle_RightEdge < screenWidth ) circle_x += movementSpeed;

			//Detecting collision between player and squre
			if (squre_BottomEdge >= circle_TopEdge &&
				squre_TopEdge <= circle_BottomEdge &&
				squre_LeftEdge <= circle_RightEdge &&
				squre_RightEdge >= circle_LeftEdge)
			{
				endGameCollision = true;
			}
		}

		EndDrawing();
	}
}