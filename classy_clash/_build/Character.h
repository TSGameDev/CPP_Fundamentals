#include "raylib.h"
#include "raymath.h"

class Character
{
public:
	Character();
	void Tick(float DELTA_TIME);
	void setScreenPos(int winWidth, int winHeight);

	Vector2 getWorldPos() { return worldPos; }
private:
	Texture2D currentTexture{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D idleTexture{ LoadTexture("characters/knight_idle_spritesheet.png") };
	Texture2D runTexture{ LoadTexture("characters/knight_run_spritesheet.png") };

	//The position of the character on the screen
	Vector2 screenPos{};
	//The position of the world map to represent character movement
	Vector2 worldPos{};

	float faceDir{ 1.f };
	float runningTime{};
	float width{};
	float height{};
	float animUpdateTime{ 1.f / 12.f };
	float speed{ 4.f };

	int currentAnimFrame{};
	int maxAnimFrames{ 6 };
};