#pragma once
#include "raylib.h"
#include "raymath.h"

class BaseCharacter
{
public:
	BaseCharacter();
	virtual void Tick(float DELTA_TIME);
	virtual Vector2 GetScreenPos() = 0;

	void UndoMovement();

	bool GetIsAlive() { return alive; }
	void SetIsAlive(bool isAlive) { alive = isAlive; }
	Vector2 GetWorldPos() { return worldPos; }
	Rectangle GetCollisionRect();

protected:
	Texture2D currentTexture{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D idleTexture{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D runTexture{ LoadTexture("characters/knight_run_spritesheet.png") };

	//The position of the character on the screen
	Vector2 screenPos{};
	//The position of the world map to represent character movement
	Vector2 worldPos{};
	Vector2 worldPosLastFrame{};
	Vector2 velocity{};

	float faceDir{ 1.f };
	float runningTime{};
	float width{};
	float height{};
	float animUpdateTime{ 1.f / 12.f };
	float speed{ 4.f };
	float characterScale{ 4.0f };

	int currentAnimFrame{};
	int maxAnimFrames{ 6 };

private:
	bool alive{ true };

};

