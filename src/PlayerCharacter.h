#pragma once
#include "raylib.h"
#include "Inventory.h"
#include <string>
#include "GameObject.h"

class PlayerCharacter : public GameObject
{

public:
	//Vector2 position;
	float speed = 100.0f;
	//Texture2D texture;

	/*Variables camara
	Borde de la pantalla
	Borde cuando se empieza a mover la camara en vez del jugador*/
	float scrollBorder = 100;
	Vector2 cameraOffset = { 0,0 };

	Inventory* inventory;

	/*void Start();
	void Update();
	void Draw();*/

	PlayerCharacter(char* _name) : GameObject(_name){}

	void Start() override;
	void Update() override;
	void Draw() override;

private:

};

