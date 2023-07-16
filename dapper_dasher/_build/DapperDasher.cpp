#include "raylib.h"

struct AnimData
{
	Rectangle rec;
	Vector2 pos;
	int frame;
	float updateTime;
	float timeSinceLastUpdate;
};

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

	int const PLAYER_SPRITESHEETDIV = 6;

	int scarfy_VelocityY = 0;
	bool playerIsGrounded = false;

	Texture2D scarfy = LoadTexture("textures/scarfy.png");
	AnimData scarfyAnimData{
		{ 0, 0, scarfy.width / PLAYER_SPRITESHEETDIV, scarfy.height },
		{ WINDOW_WIDTH / 2 - scarfy.width / 2, WINDOW_HEIGHT - scarfy.height },
		0,
		1.0 / 12.0,
		0
	};

#pragma endregion

#pragma region Nebula Variables

	int const NEBULA_SPRITESHEETDIV = 8;

	int nebula_VelocityX = -300;

	Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png");
	AnimData nebulaAnimData{
		{ 0.0, 0.0, nebula.width / NEBULA_SPRITESHEETDIV, nebula.height / NEBULA_SPRITESHEETDIV },
		{ WINDOW_WIDTH, WINDOW_HEIGHT - nebula.height },
		0,
		1.0 / 12,
		0
	};



#pragma endregion


	SetTargetFPS(60);
	while (!WindowShouldClose())
	{
		//get delta time, time between frames
		float const DELTA_TIME = GetFrameTime();

		BeginDrawing();
		ClearBackground(WHITE);

		//If player is grounded, set bool true, set velocity 0 and correctly position player
		if (scarfyAnimData.pos.y >= WINDOW_HEIGHT - scarfyAnimData.rec.height)
		{
			playerIsGrounded = true;
			scarfy_VelocityY = 0;
			scarfyAnimData.pos.y = WINDOW_HEIGHT - scarfyAnimData.rec.height;
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

		//Update nebula Pos
		nebulaAnimData.pos.x += nebula_VelocityX * DELTA_TIME;

		//Update player Y POS with Y Velocity
		scarfyAnimData.pos.y += scarfy_VelocityY * DELTA_TIME;

		//Animate Nebula
		nebulaAnimData.timeSinceLastUpdate += DELTA_TIME;
		if (nebulaAnimData.timeSinceLastUpdate >= nebulaAnimData.updateTime)
		{
			nebulaAnimData.timeSinceLastUpdate = 0;

			if (nebulaAnimData.frame >= NEBULA_SPRITESHEETDIV - 1)
				nebulaAnimData.frame = 0;
			nebulaAnimData.rec.x = nebulaAnimData.frame * nebulaAnimData.rec.width;
			nebulaAnimData.frame++;
		}

		//Animate Scarfy
		scarfyAnimData.timeSinceLastUpdate += DELTA_TIME;
		if (scarfyAnimData.timeSinceLastUpdate >= scarfyAnimData.updateTime && playerIsGrounded)
		{
			scarfyAnimData.timeSinceLastUpdate = 0;

			if (scarfyAnimData.frame >= PLAYER_SPRITESHEETDIV - 1)
				scarfyAnimData.frame = 0;
			scarfyAnimData.rec.x = scarfyAnimData.frame * scarfyAnimData.rec.width;
			scarfyAnimData.frame++;
		}

		//Draw nebula
		DrawTextureRec(nebula, nebulaAnimData.rec, nebulaAnimData.pos, WHITE);

		//Draw Scarfy
		DrawTextureRec(scarfy, scarfyAnimData.rec, scarfyAnimData.pos, WHITE);

		EndDrawing();
	}
	UnloadTexture(scarfy);
	UnloadTexture(nebula);
	CloseWindow();
}