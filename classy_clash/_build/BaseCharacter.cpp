#include "BaseCharacter.h"

BaseCharacter::BaseCharacter()
{

}

void BaseCharacter::Tick(float DELTA_TIME)
{
	//storing worldpos
	worldPosLastFrame = worldPos;

	//Update Aniamtion
	runningTime += DELTA_TIME;
	if (runningTime >= animUpdateTime)
	{
		currentAnimFrame++;
		runningTime = 0.0;
		if (currentAnimFrame >= maxAnimFrames) currentAnimFrame = 0;
	}

	//Move the map relative to the inverse of the direction inputs
	if (Vector2Length(velocity) != 0.0)
	{
		worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(velocity), speed));
		faceDir = static_cast<float>(velocity.x) < 0.f ? -1.f : 1.f;
		currentTexture = runTexture;
	}
	else
	{
		currentTexture = idleTexture;
	}
	velocity = {};

	//Draw Player Textures with scale
	Rectangle CharacterAnimFrame = { currentAnimFrame * width, 0.f, faceDir * width, height };
	Rectangle CharacterDest = { GetScreenPos().x,  GetScreenPos().y, width * characterScale, height * characterScale };
	DrawTexturePro(currentTexture, CharacterAnimFrame, CharacterDest, Vector2{ 0.0f, 0.0f }, 0.0f, WHITE);
}

void BaseCharacter::UndoMovement()
{
	worldPos = worldPosLastFrame;
}

Rectangle BaseCharacter::GetCollisionRect()
{
	return Rectangle
	{
		GetScreenPos().x,
		GetScreenPos().y,
		width * characterScale,
		height * characterScale
	};
}