#pragma once
#include <string>
#include "raylib.h"

extern "C" 
{
	#include "md5.h"
}

class GameObject
{
protected:
	std::string name;

	//si esta enabled se llaman los metodos de update y draw
	bool enabled = true;

public:
	//unique id en MD5
	uint8_t uid[16]; //arreglo de 16
	Vector2 position;
	Texture2D texture;

	bool drawDebugUID = false;


	//Constructor recibe un nombre y computa el md5
	GameObject(char* _name) 
	{
		name = _name;
		md5String(_name, uid);
		position = { 0,0 };
		texture = { 0 }; //Estructura
	}

	virtual void Start() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	void PrintUID();

	std::string getUID()
	{
		std::string uidString;
		for (int i = 0; i < 16; i++)
		{
			char buffer[3];
			sprintf(buffer, "%02X", uid[i]);
			uidString += buffer;
		}
		return uidString;
	}

	//getters y setters 
	void setEnabled(bool _enabled)
	{
		enabled = _enabled;
	}
	bool isEnabled()
	{
		return enabled;
	}

};

