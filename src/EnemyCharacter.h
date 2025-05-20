#pragma once
#include "GameObject.h"
#include "PlayerCharacter.h"
class EnemyCharacter : public GameObject
{
public:
	float speed = 8.0f;
	PlayerCharacter* target;

	EnemyCharacter(char* _name, PlayerCharacter* _target) : GameObject(_name), target(_target) {}

	void Start() override;
	void Update() override;
	void Draw() override;

private:
};

