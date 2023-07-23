#pragma once
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
public:
	Character(int winWidth, int winHeight);

	virtual void Tick(float DELTA_TIME) override;
	virtual Vector2 GetScreenPos() override;

	void TakeDamage(float damage);

	Rectangle GetWeaponCollisionRect() { return weaponCollisionRect; }
	float GetHealth() const { return health; }

private:
	float windowWidth{};
	float windowHeight{};
	Texture2D weapon{ LoadTexture("characters/weapon_sword.png") };
	Rectangle weaponCollisionRect{};
	float health{ 100.f };
};