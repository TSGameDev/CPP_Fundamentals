#include "Character.h"

Character::Character(int winWidth, int winHeight)
{
	width = static_cast<float>(currentTexture.width) / maxAnimFrames;
	height = currentTexture.height;

	screenPos =
	{
		static_cast<float>(winWidth) / 2.0f - characterScale * (0.5f * width),
		static_cast<float>(winHeight) / 2.0f - characterScale * (0.5f * height)
	};
}

void Character::Tick(float DELTA_TIME)
{
	//Inputs
	Vector2 dir = { 0,0 };
	if (IsKeyDown(KEY_A)) dir.x -= 1.0f;
	if (IsKeyDown(KEY_D)) dir.x += 1.0f;
	if (IsKeyDown(KEY_W)) dir.y -= 1.0f;
	if (IsKeyDown(KEY_S)) dir.y += 1.0f;

	//storing worldpos
	worldPosLastFrame = worldPos;

	//Move the map relative to the inverse of the direction inputs
	if (Vector2Length(dir) != 0.0)
	{
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(dir), speed));
		faceDir = static_cast<float>(dir.x) < 0.f ? -1.f : 1.f;
		currentTexture = runTexture;
	}
	else
	{
		currentTexture = idleTexture;
	}

	//Update Aniamtion
	runningTime += DELTA_TIME;
	if (runningTime >= animUpdateTime)
	{
		currentAnimFrame++;
		runningTime = 0.0;
		if (currentAnimFrame >= maxAnimFrames) currentAnimFrame = 0;
	}

	//Draw Player Textures with scale
	Rectangle knightAnimFrame = { currentAnimFrame * width, 0.f, faceDir * width, height};
	Rectangle knightDest = { screenPos.x, screenPos.y, width * characterScale, height * characterScale };
	DrawTexturePro(currentTexture, knightAnimFrame, knightDest, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);

}

void Character::UndoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle Character::GetCollisionRect()
{
	return Rectangle
	{
		screenPos.x,
		screenPos.y,
		width * characterScale,
		height * characterScale
	};
}