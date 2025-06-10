/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/
*/

#include "raylib.h"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "resource_dir.h"
#include <limits>
#include <cstring>
#include <cstdio>
#include <queue>

#include "LinkedList.h"
#include "Inventory.h"
#include "PlayerCharacter.h"
#include "Stack.h"
#include "Queue.h"
#include "PanelMensaje.h"
#include "GameObject.h"
#include "EnemyCharacter.h"
#include "Heap.h"

#include <unordered_map>

extern "C" 
{
	#include "md5.h"
}

typedef std::vector<std::vector<int>> Map2D; //Array mapa 

//Mapeado
void LoadMap(Map2D& _map, size_t _x, size_t _y, const std::string& filename)
{
	std::ifstream filemap(filename);
	if (filemap.is_open())
	{
		char c;
		for (size_t j = 0; j < _y; j++)
		{
			for (size_t i = 0; i < _x; i++)
			{
				filemap.get(c);
				if (filemap.eof())
				{
					std::cout << "final inesperado del archivo de mapa" << std::endl;
					return;
				}
				_map[j][i] = c - '0';
			}
			filemap.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			printf("\n");
		}
	}
	else
	{
		std::cout << "No se pudo abrir el archivo de mapa" << std::endl;
		return;
	}
}

//Musica
Music LoadBGM()
{
	const char* defaultBGM = "TECNO1.XM";
	std::fstream configfile("config.ini");
	if (configfile.is_open())
	{
		std::string linea;
		char buffer[64];
		while (std::getline(configfile, linea))
		{
			std::cout << "Linea leida: " << linea << std::endl;
			char* llave = strtok((char*)linea.c_str(), "=");
			if (strcmp("music", llave) == 0)
			{
				char* valor = strtok(NULL, "=");
				std::cout << "Se encontró la llave music" << std::endl;
			}
		}
	}
	else
	{
		std::cout << "No se pudo abrir el archivo config.ini, usando BGM default" << std::endl;
		return LoadMusicStream("TECNO1.XM");
	}
}

//Tabla de UID
void VolcarTablaUIDs(const std::unordered_map<std::string, std::string>& table)
{
	std::cout << "\n=== Tabla de UIDs ===\n";
	for (const auto& pair : table)
	{
		std::cout << "UID: " << pair.first << " -> Nombre: " << pair.second << std::endl;
	}
}

//Eventos de Heap
struct Evento
{
	std::string descripcion;
	int prioridad;

	bool operator<(const Evento& otro) const
	{
		return prioridad < otro.prioridad;
	}
};

int main()
{
	//Prueba de lista ligada
	int a = 16;
	LLNode<int>* nodo = new LLNode<int>(&a);

	LinkedList<int>* lista = new LinkedList<int>(nodo);
	lista->AddNode(new int(28));
	lista->AddNode(new int(42));
	lista->RemoveLastNode();

	//Prueba de stack o pila
	Stack<float> pila(10);
	std::cout << "Pila vacia: " << std::boolalpha << pila.IsEmpty() << std::endl;
	pila.push(1.0f);
	pila.push(3.1416);
	pila.push(2.71828);
	std::cout << "num de elementos de la pila: " << pila.size() << std::endl;
	float temp = pila.pop();
	std::cout << "num de elementos de la pila: " << pila.size() << std::endl;

	//Prueba de Queue o cola
	Queue<int> q = Queue<int>(3);
	std::cout << "Cola vacia: " << std::boolalpha << q.IsEmpty() << std::endl;
	q.enqueue(10);
	q.enqueue(24);
	q.enqueue(42);
	q.debugPrintContents();
	q.enqueue(99);
	q.debugPrintContents();
	int temp2 = q.dequeue();
	temp2 = q.dequeue();
	temp2 = q.dequeue();
	q.debugPrintContents();
	q.enqueue(24);
	q.debugPrintContents();
	std::cout << "num de elementos de la cola: " << q.size() << std::endl;
	std::cout << "peek: " << *q.peek() << std::endl;
	int temp3 = q.dequeue();
	q.debugPrintContents();

	std::vector<int> misdatos(15, 0);
	for (int i = 0; i < 15; i++)
		std::cout << "valor: " << misdatos[i] << std::endl;

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	int tileSize = 30;
	int maxTilesH = 25;
	int maxTilesV = 20;

	//Pantalla inicial
	InitWindow(maxTilesH * tileSize, maxTilesV * tileSize, "Tiles");

	Map2D mapa(maxTilesV, std::vector<int>(maxTilesH, 0));

	SearchAndSetResourceDir("resources");

	const char* mapNames[3] = { "map.txt", "map2.txt", "map3.txt" };
	int selectedMapIndex = 0;
	bool mapSelected = false;
	//Selección de mapa
	while (!mapSelected && !WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
		DrawText("Seleccionar mapa con 1, 2 o 3", 20, 20, 20, YELLOW);
		DrawText("Mapa 1 (1)", 20, 50, 20, WHITE);
		DrawText("Mapa 2 (2)", 20, 80, 20, WHITE);
		DrawText("Mapa 3 (3)", 20, 110, 20, WHITE);
		EndDrawing();
		if (IsKeyPressed(KEY_ONE)) { selectedMapIndex = 0; mapSelected = true; }
		if (IsKeyPressed(KEY_TWO)) { selectedMapIndex = 1; mapSelected = true; }
		if (IsKeyPressed(KEY_THREE)) { selectedMapIndex = 2; mapSelected = true; }
	}

	//Crear jugador
	//Inventario
	Inventory* inventario = new Inventory();
	inventario->AddItem(new Item("Espada", 1));
	inventario->AddItem(new Item("Pocion", 2));
	inventario->AddItem(new Item("Mondongo", 3));
	inventario->debugPrintContents();

	PlayerCharacter* player = new PlayerCharacter("Player1");
	player->Start();
	player->inventory = inventario;
	player->PrintUID();

	//Panelmensaje
	PanelMensaje* panel = new PanelMensaje(GetScreenWidth() - 210, 200, 50, 2);

	//Para prueba, simularemos que obtiene de golpe un pujado de logros
	std::queue<std::string> mensajePendiente;
	mensajePendiente.push("Logro: thief");
	mensajePendiente.push("Logro: gossip");
	mensajePendiente.push("Logro: fisher");
	mensajePendiente.push("Logro: hoarder");

	//Heap
	Heap<Evento> eventos;
	eventos.Insert({ "E: Tomar agua", 8 });
	eventos.Insert({ "E: Comer algo", 5 });
	eventos.Insert({ "E: Burlarse", 3 });

	if (!eventos.IsEmpty()) 
	{
		panel->Show(eventos.Peek().descripcion);
	}

	//Prueba de calculo de hash md5 usando la biblioteca de zunawe
	uint8_t result[16];
	char* mensaje = "hola mundo";
	md5String(mensaje, result); //Se almacena result
	//Imprimir hash en hexadecimal
	//printhash
	for (int i = 0; i < 16; i++)
	{
		printf("%02X", result[i]);
	}

	//Arreglo de GameObjects y la tabla de UIDs
	std::vector<GameObject*> gameobjects;
	std::unordered_map<std::string, std::string> objectTable;

	//Helper para convertir MD5 bytes a string hex
	auto md5ToHex = [&](const uint8_t bytes[16]) 
		{
		char buf[33];
		for (int i = 0;i < 16;i++) sprintf(buf + 2 * i, "%02X", bytes[i]);
		buf[32] = '\0';
		return std::string(buf);
		};

	//Insertar player
	gameobjects.push_back(player);
	// md5String ya llenó player->uid en el constructor
	objectTable[md5ToHex(player->uid)] = "Player1";

	//Creamos 3 enemigos
	for (int i = 0; i < 3; i++)
	{
		char nameBuf[16];
		sprintf(nameBuf, "Enemy%d", i + 1);
		EnemyCharacter* e = new EnemyCharacter(nameBuf, player);
		e->Start();
		//Posiciones iniciales separadas
		e->position = { 80.0f + 180.0f * i,  60.0f + 50.0f * (i % 2) };
		gameobjects.push_back(e);
		objectTable[md5ToHex(e->uid)] = nameBuf;
	}

	VolcarTablaUIDs(objectTable);

	LoadMap(mapa, maxTilesH, maxTilesV, mapNames[selectedMapIndex]);

	enum Tiletype
	{
		tierra, piedra, madera, metal
	};
	Texture tiles[4];
	tiles[0] = LoadTexture("tierra.png");
	tiles[1] = LoadTexture("piedra.png");
	tiles[2] = LoadTexture("madera.png");
	tiles[3] = LoadTexture("metal.png");

	InitAudioDevice();
	Music bgm = LoadMusicStream("TECNO1.XM");
	PlayMusicStream(bgm);

	//Borde de la pantalla
	//Borde cuando se empieza a mover la camara en vez del jugador
	//float scrollBorder = 0.4f * GetScreenHeight();

	char buffer[64];

	//Game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(bgm);

		for (auto obj : gameobjects) 
			if (obj->isEnabled())
				obj->Update();

		//Paneles
		panel->update();

		if (!mensajePendiente.empty() && panel->position.y <= -panel->size.y) 
		{
			panel->Show(mensajePendiente.front());
			mensajePendiente.pop();
		}
		//Easter Egg
		if (IsKeyPressed(KEY_SPACE))
		{
			panel->Show("Hola profe");
		}
		//Hacer la tarea
		if (IsKeyPressed(KEY_E))
		{
			if (!eventos.IsEmpty())
			{
				eventos.Extract(); //Quitar el evento actual
				if (!eventos.IsEmpty())
					panel->Show(eventos.Peek().descripcion); //Mostrar el siguiente
				else
					panel->Show("No hay mas eventos");
			}
		}

		BeginDrawing();
		ClearBackground(BLACK);
		for (int i = 0; i < maxTilesV; i++)
		{
			for (int j = 0; j < maxTilesH; j++)
			{
				DrawTexture(tiles[mapa[i][j]], j * tileSize - player->cameraOffset.x, i * tileSize - player->cameraOffset.y, WHITE);
			}
		}
		DrawText("TILES", 20, 20, 20, YELLOW);
		sprintf(buffer, "CAMOFFSET: %.3f, %.3f", player->cameraOffset.x, player->cameraOffset.y);
		DrawText(buffer, 20, 40, 20, YELLOW);
		sprintf(buffer, "FPS: %.3f", 1/GetFrameTime()); //f=1/periodo  0.016 seg = 60 htz o 60 fps
		DrawText(buffer, 20, 60, 20, YELLOW);

		for (auto obj : gameobjects) 
			if (obj->isEnabled())
				obj->Draw();

		//UI
		panel->draw();

		EndDrawing();
	}
	for (auto obj : gameobjects) 
	{
		delete obj;
	}

	UnloadTexture(tiles[4]);
	CloseWindow();
	return 0;
}
