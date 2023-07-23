#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture)
{
    worldPos = pos;
    currentTexture = idle_texture;
    idleTexture = idle_texture;
    runTexture = run_texture;
    width = static_cast<float>(currentTexture.width) / maxAnimFrames;
    height = static_cast<float>(currentTexture.height);
    speed = 3.f;
}

Vector2 Enemy::GetScreenPos()
{
    return Vector2Subtract(worldPos, target->GetWorldPos());
}

void Enemy::Tick(float DELTA_TIME)
{
    if (!GetIsAlive()) return;

    velocity = Vector2Subtract(target->GetScreenPos(), GetScreenPos());
    if (Vector2Length(velocity) < radius) velocity = {};

	//Call Parent Tick
	BaseCharacter::Tick(DELTA_TIME);

    if (CheckCollisionRecs(target->GetCollisionRect(), GetCollisionRect()))
    {
        target->TakeDamage(damagePerSecond * DELTA_TIME);
    }
}