#include "raylib.h"

int main()
{
#pragma region Window_Init

	int const WINDOW_WIDTH = 512;
	int const WINDOW_HEIGHT = 380;
	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Dapper Dasher");

#pragma endregion

#pragma region Const Values - Magic Numbers

	int const JUMPFORCE = -600;
	int const GRAVITY = 1000;

#pragma endregion

#pragma region Player Variables

	int const PLAYER_ANIMFRAME_MAX = 6;
	float const PLAYER_ANIMUPDATETIME = 1.0 / 12.0;

	int scarfy_VelocityY = 0;
	int scarfy_AnimFrame = 0;
	float scarfy_TimeSinceLastAnimFrame = 0;
	bool playerIsGrounded = false;

	Texture2D scarfy = LoadTexture("textures/scarfy.png");

	Rectangle scarfyRect;
	scarfyRect.width = scarfy.width / PLAYER_ANIMFRAME_MAX;
	scarfyRect.height = scarfy.height;
	scarfyRect.x = 0;
	scarfyRect.y = 0;

	Vector2 scarfyPos;
	scarfyPos.x = WINDOW_WIDTH / 2 - scarfyRect.width / 2;
	scarfyPos.y = WINDOW_HEIGHT - scarfyRect.height;

#pragma endregion

#pragma region Nebula Variables

	int nebula_VelocityX = 0;

	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");


#pragma endregion


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		//get delta time, time between frames
		float const DELTA_TIME = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		//If player is grounded, set bool true, set velocity 0 and correctly position player
		if (scarfyPos.y >= WINDOW_HEIGHT - scarfyRect.height)
		{
			playerIsGrounded = true;
			scarfy_VelocityY = 0;
			scarfyPos.y = WINDOW_HEIGHT - scarfyRect.height;
		}
		//Else set bool false, add gravity each frame
		else
		{
			playerIsGrounded = false;
			scarfy_VelocityY += GRAVITY * DELTA_TIME;
		}

		//Jump check, needs to be grounded and space key press
		if (IsKeyPressed(KEY_SPACE) && playerIsGrounded)
		{
			scarfy_VelocityY += JUMPFORCE;
			playerIsGrounded = false;
		}

		//Update player Y POS with Y Velocity
		scarfyPos.y += scarfy_VelocityY * DELTA_TIME;

		//Animate Scarfy
		scarfy_TimeSinceLastAnimFrame += DELTA_TIME;
		if (scarfy_TimeSinceLastAnimFrame >= PLAYER_ANIMUPDATETIME)
		{
			scarfy_TimeSinceLastAnimFrame = 0;

			if (scarfy_AnimFrame > PLAYER_ANIMFRAME_MAX)
				scarfy_AnimFrame == 0;
			scarfyRect.x = scarfy_AnimFrame * scarfyRect.width;
			scarfy_AnimFrame++;
		}

		//Draw Scarfy
		DrawTextureRec(scarfy, scarfyRect, scarfyPos, WHITE);

		EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
}