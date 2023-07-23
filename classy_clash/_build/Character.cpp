#include "Character.h"

Character::Character(int winWidth, int winHeight) : 
	windowWidth(winWidth),
	windowHeight(winHeight)
{
	width = static_cast<float>(currentTexture.width) / maxAnimFrames;
	height = currentTexture.height;
}

Vector2 Character::GetScreenPos()
{
	return Vector2
	{
		static_cast<float>(windowWidth) / 2.0f - characterScale * (0.5f * width),
		static_cast<float>(windowHeight) / 2.0f - characterScale * (0.5f * height)
	};
}

void Character::TakeDamage(float damage)
{
	health -= damage;
	if (health <= 0.f)
	{
		SetIsAlive(false);
	}
}

void Character::Tick(float DELTA_TIME)
{
	if (!GetIsAlive()) return;

	if (IsKeyDown(KEY_A)) velocity.x -= 1.0f;
	if (IsKeyDown(KEY_D)) velocity.x += 1.0f;
	if (IsKeyDown(KEY_W)) velocity.y -= 1.0f;
	if (IsKeyDown(KEY_S)) velocity.y += 1.0f;

	//Call Parent Tick
	BaseCharacter::Tick(DELTA_TIME);

	//Draw Weapon
	Vector2 weaponOrigin{};
	Vector2 weaponOffset{};
	float WeaponRotation{};
	if (faceDir > 0.f)
	{
		//facing right
		weaponOrigin = {0.f, weapon.height * characterScale};
		weaponOffset = {35.f, 55.f};
		weaponCollisionRect =
		{
			GetScreenPos().x + weaponOffset.x,
			GetScreenPos().y + weaponOffset.y - weapon.height * characterScale,
			weapon.width * characterScale,
			weapon.height * characterScale
		};
		WeaponRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? 35.f : 0.f;
	}
	else
	{
		//facing left
		weaponOrigin = { weapon.width * characterScale, weapon.height * characterScale };
		weaponOffset = { 25.f, 55.f };
		weaponCollisionRect =
		{
			GetScreenPos().x + weaponOffset.x - weapon.width * characterScale,
			GetScreenPos().y + weaponOffset.y - weapon.height * characterScale,
			weapon.width * characterScale,
			weapon.height * characterScale
		};
		WeaponRotation = IsMouseButtonDown(MOUSE_BUTTON_LEFT) ? -35.f : 0.f;
	}
	
	Rectangle weaponSource{0.f, 0.f, static_cast<float>(weapon.width) * faceDir, static_cast<float>(weapon.height) };
	Rectangle weaponDest{GetScreenPos().x + weaponOffset.x, GetScreenPos().y + weaponOffset.y, weapon.width * characterScale, weapon.height * characterScale};
	DrawTexturePro(weapon, weaponSource, weaponDest, weaponOrigin, WeaponRotation, WHITE);
}
