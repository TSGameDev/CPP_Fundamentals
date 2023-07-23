#pragma once
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
public:
	Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);

	virtual void Tick(float DELTA_TIME) override;
	virtual Vector2 GetScreenPos() override;

	void SetTarget(Character* newTarget) { target = newTarget; }

private:
	Character* target{};
	float damagePerSecond{ 10.f };
	float radius{ 25.f };
};

