#pragma once
#include "raylib.h"
#include "raymath.h"

class Prop
{
public:
	Prop(Texture2D texture, Vector2 worldPos);
	void Render(Vector2 knightPos);
	Rectangle GetCollisionRect(Vector2 knightPos);

private:
	Texture2D texture{};
	Vector2 worldPos{};
	float scale{4.0f};

};

