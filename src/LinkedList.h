#pragma once
#include <iostream>
#include "LLNode.h"

template <class T>
class LinkedList
{
protected:
	LLNode<T> *head;

public:
	//Lista vacia
	LinkedList() : head(nullptr) {}
	LinkedList(LLNode<T> *_hd) : head(_hd) {}

	//Imprimir el contenido
	//void PrintElements();

	//Agrega un elemento al final de la lista
	LLNode<T>* AddNode(T* _data) 
	{
		//Si la lista esta vacia
		if (head == nullptr) 
		{
			head = new LLNode<T>(_data);
			return head;
		}
		//Si no, iterar hasta el final
		LLNode<T>* iter = head;
		while (iter->next != nullptr)
			iter = iter->next;
		iter->next = new LLNode<T>(_data);

		return iter->next;
	}

	//Remover el ultimo nodo
	void RemoveLastNode()
	{
		if (head == nullptr)
			return;
		//Si solo hay un nodo
		if (head->next == nullptr) 
		{
			delete head;
			head = nullptr;
			return;
		}

		LLNode<T>* iter = head;
		while (iter->next->next != nullptr)
			iter = iter->next;
		delete iter->next;
		iter->next = nullptr;
	}

};

//NULL = 0 -> C
//nullptr = 0 -> C++  apuntador nulo