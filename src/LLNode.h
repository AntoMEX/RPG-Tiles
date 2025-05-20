#pragma once

template <class T>
class LLNode
{
public:

	//Referencia al siguiente nodo de la lista
	LLNode<T> *next;

	//Lista ligada almacena floats
	T* data;

	//Constructores
	//Polimorfismo de POO
	LLNode(T* _data) : data(_data), next(nullptr) {} //Valor ini de data, valor de next vacio
	LLNode(T* d, LLNode<T>* nxt) : data(d), next(nxt) {} 
};

