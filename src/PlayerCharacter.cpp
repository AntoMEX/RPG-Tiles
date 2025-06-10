#include "PlayerCharacter.h"

void PlayerCharacter::Start()
{
	texture = LoadTexture("wabbit_alpha.png");

	inventory = new Inventory();

	//Posicion inicial
	position = {(float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 };
	speed = 100;

	scrollBorder = GetScreenHeight() * 0.3f;
}

void PlayerCharacter::Draw()
{
	DrawTexture(texture, position.x, position.y, WHITE);
	DrawText("PLAYER", position.x, position.y - 40, 10, WHITE);
	DrawText(getUID().c_str(), position.x, position.y - 20, 10, WHITE);
	//hud

	DrawRectangle(10, 10, 100, 30, WHITE);

	if (inventory != nullptr && inventory->currentItem != nullptr)
	{
		DrawText(inventory->currentItem->data->name.c_str(), 20, 20, 20, BLACK);

	}
	else
	{
		DrawText("EMPTY", 20, 20, 20, BLACK);
	}
}

void PlayerCharacter::Update()
{
	if (IsKeyDown(KEY_W))
	{
		position.y -= speed * GetFrameTime();
		if (position.y < scrollBorder)
		{
			position.y = scrollBorder;
			cameraOffset.y -= speed * GetFrameTime();
		}
	}

	if (IsKeyDown(KEY_A))
	{
		position.x -= speed * GetFrameTime();
		if (position.x < scrollBorder)
		{
			position.x = scrollBorder;
			cameraOffset.x -= speed * GetFrameTime();
		}
	}

	if (IsKeyDown(KEY_S))
	{
		position.y += speed * GetFrameTime();
		if (position.y > GetScreenHeight() - scrollBorder)
		{
			position.y = GetScreenHeight() - scrollBorder;
			cameraOffset.y += speed * GetFrameTime();
		}
	}

	if (IsKeyDown(KEY_D))
	{
		position.x += speed * GetFrameTime();
		if (position.x > GetScreenWidth() - scrollBorder)
		{
			position.x = GetScreenWidth() - scrollBorder;
			cameraOffset.x += speed * GetFrameTime();
		}
	}

	if (IsKeyPressed(KEY_RIGHT))
	{
		//Asume que siempre tiene inventory
		inventory->nextItem();
	}
	if (IsKeyPressed(KEY_LEFT)) {
		inventory->prevItem();
	}
}
