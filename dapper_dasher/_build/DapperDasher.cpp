#include "raylib.h"

int main()
{
	//Window Init
	int const WINDOW_WIDTH = 512;
	int const WINDOW_HEIGHT = 380;
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

	//Global Values
	int const JUMPFORCE = -20;
	int const GRAVITY = 1;

	//Player Values
	int player_YPos = WINDOW_HEIGHT - 100;
	int player_VelocityY = 0;

	bool playerIsGrounded = false;

	//Temporary Player Values
	int squreWidth = 50;
	int squreHeight = 80;


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		//If player is grounded, set bool true, set velocity 0 and correctly position player
		if (player_YPos >= WINDOW_HEIGHT - squreHeight)
		{
			playerIsGrounded = true;
			player_VelocityY = 0;
			player_YPos = WINDOW_HEIGHT - squreHeight;
		}
		//Else set bool false, add gravity each frame
		else
		{
			playerIsGrounded = false;
			player_VelocityY += GRAVITY;
		}

		//Jump check, needs to be grounded and space key press
		if (IsKeyPressed(KEY_SPACE) && playerIsGrounded)
		{
			player_VelocityY += JUMPFORCE;
			playerIsGrounded = false;
		}

		//Update player Y POS with Y Velocity
		player_YPos += player_VelocityY;

		//Display Temporary Player
		DrawRectangle(WINDOW_WIDTH / 2, player_YPos, squreWidth, squreHeight, BLUE);

		EndDrawing();
	}
	CloseWindow();
}