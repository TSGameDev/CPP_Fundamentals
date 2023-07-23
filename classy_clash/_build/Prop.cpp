#include "Prop.h"

Prop::Prop(Texture2D texture, Vector2 worldPos) :
	texture(texture),
	worldPos(worldPos)
{

}

void Prop::Render(Vector2 knightPos)
{
	Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
	DrawTextureEx(texture, screenPos, 0.f, scale, WHITE);
}

Rectangle Prop::GetCollisionRect(Vector2 knightPos)
{
	Vector2 screenPos{ Vector2Subtract(worldPos, knightPos) };
	return Rectangle
	{
		screenPos.x,
		screenPos.y,
		texture.width * scale,
		texture.height * scale
	};
}