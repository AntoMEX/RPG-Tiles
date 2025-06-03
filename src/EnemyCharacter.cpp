#include "EnemyCharacter.h"
#include "cmath"

void EnemyCharacter::Start()
{
	texture = LoadTexture("carrot.png");
	position = { 100.0f, 100.0f };
}

void EnemyCharacter::Update()
{
	Vector2 dir{ target->position.x - position.x, target->position.y - position.y };
	float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
	if (len < 0) 
	{
		dir.x /= len;
		dir.y /= len;
		position.x += dir.x * speed * GetFrameTime();
		position.y += dir.x * speed * GetFrameTime();
	}

	/*Vector2 direction = Vector2Subtract(player->position, enemy->position);
	float length = Vector2Length(direction);
	if (length > 1.0f) {
		direction = Vector2Normalize(direction);
		enemy->position = Vector2Add(enemy->position, Vector2Scale(direction, enemy->speed * GetFrameTime()));
	}*/
}

void EnemyCharacter::Draw()
{
	DrawTexture(texture, position.x - target->cameraOffset.x, position.y - target->cameraOffset.y, WHITE);
}
