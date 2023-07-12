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
	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	Rectangle scarfyAnimRect;
	scarfyAnimRect.width = scarfy.width / 6;
	scarfyAnimRect.height = scarfy.height;
	scarfyAnimRect.x = 0;
	scarfyAnimRect.y = 0;
	Vector2 scarfyPos;
	scarfyPos.x = WINDOW_WIDTH / 2 - scarfyAnimRect.width / 2;
	scarfyPos.y = WINDOW_HEIGHT - scarfyAnimRect.height;

	int scarfy_VelocityY = 0;

	bool playerIsGrounded = false;


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		//If player is grounded, set bool true, set velocity 0 and correctly position player
		if (scarfyPos.y >= WINDOW_HEIGHT - scarfyAnimRect.height)
		{
			playerIsGrounded = true;
			scarfy_VelocityY = 0;
			scarfyPos.y = WINDOW_HEIGHT - scarfyAnimRect.height;
		}
		//Else set bool false, add gravity each frame
		else
		{
			playerIsGrounded = false;
			scarfy_VelocityY += GRAVITY;
		}

		//Jump check, needs to be grounded and space key press
		if (IsKeyPressed(KEY_SPACE) && playerIsGrounded)
		{
			scarfy_VelocityY += JUMPFORCE;
			playerIsGrounded = false;
		}

		//Update player Y POS with Y Velocity
		scarfyPos.y += scarfy_VelocityY;

		//Display Temporary Player
		DrawTextureRec(scarfy, scarfyAnimRect, scarfyPos, WHITE);

		EndDrawing();
	}
	UnloadTexture(scarfy);
	CloseWindow();
}