#pragma once
#include "raylib.h"
#include <string>

enum PanelState
{
	hidden, moving, showing
};

class PanelMensaje
{
private:
	float timer;
	float desiredPositionY;
	PanelState state = hidden;

public:
	Vector2 position;
	Vector2 size;

	int timeOnScreen;

	std::string message;

	PanelMensaje(float posx, float width, float height, int _timeOnScreen)
	{
		position = { posx, -height }; //Inicia fuera de la pantalla
		size = { width, height };
		timeOnScreen = _timeOnScreen;
		timer = 0;
		desiredPositionY = -height;
		state = hidden;
	}

	void update()
	{
		if (state == hidden)
		{
			return;
		}
		else if (state == moving)
		{
			//Interpolacion de movimiento
			if (position.y != desiredPositionY)
			{
				//lerp position, lerp cada ciclo resta la posicion deseada (final) menos la posición actual
				position.y += (desiredPositionY - position.y) * 10.0f * GetFrameTime();
			}
			if (abs(desiredPositionY - position.y) < 0.1f)
			{
				position.y = desiredPositionY;
				state = showing;
				timer = 0;

				if (desiredPositionY < 0) 
				{
					state = hidden;
				}
				else 
				{
					state = showing;
				}
			}
		}
		else if (state == showing)
		{
			timer += GetFrameTime();
			if (timer > timeOnScreen) 
			{
				desiredPositionY = -size.y - 10;
				state = moving;
			}
		}
	}

	void draw()
	{
		DrawRectangle(position.x, position.y, size.x, size.y, DARKGREEN);
		DrawRectangleLines(position.x, position.y, size.x, size.y, WHITE);
		DrawText(message.c_str(), position.x + 10, position.y + 10, 20, WHITE);
	}

	void Show(std::string msg)
	{
		//Mensaje se guarde en stack cada vez que se mande a llamar el show

		state = moving;
		timer = 0;
		message = msg;
		desiredPositionY = 10; //10 pixeles en alto de pantalla
		position.y = -size.y - 10;
	}
};

