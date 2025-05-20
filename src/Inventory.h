#pragma once
#include "LinkedList.h"
#include "Item.h"

class Inventory :
	public LinkedList<Item>
{

public:
	//constructor
	Inventory() : LinkedList<Item>() {}
	//agregar item al inventario
	void AddItem(Item* _item);

	void nextItem();

	void debugPrintContents();

	LLNode<Item>* currentItem;

};

