#pragma once

template <typename T>
class Queue
{
private:
	T* data;
	size_t front;
	size_t rear;
	size_t maxsize;

public:
	//Contructor
	Queue(size_t _size)
	{
		maxsize = _size;
		front = 0;
		rear = 0;
		data = new T[maxsize];
	}

	//Destructor
	~Queue() 
	{
		delete[] data;
	}

	bool IsEmpty() 
	{
		return front == rear; //Comprobacion vacia, si es igual la cola que el frente
	}

	size_t size() 
	{
		return rear - front; 
	}

	//Agregar elemento de la cola
	void enqueue(T item)
	{
		if (size() == maxsize) //Si es igual al maximo
		{
			std::cout << "La cola esta llena, queue overflow" << std::endl; //no se puede llenar mas
			return;
		}
		data[rear++] = item; //Si hay espacio, agrega elemento, la cola aumenta
	}

	//Quitar elemento de la cola
	T dequeue()
	{
		if (IsEmpty()) //Si esta vacia
		{
			std::cout << "La cola esta vacia" << std::endl; //No se puede quitar nada
			return T();
		}

		T temp = data[front]; //Se guarda el valor
		for (size_t i = front; i < rear; i++) //Si hay elementos quita el del frente
		{
			data[i] = data[i + 1];
		}
		rear--;
		return temp; 
	}

	//Ver el primer elemento de la cola
	T* peek()
	{
		if (IsEmpty())
		{
			std::cout << "La cola esta vacia" << std::endl;
			return nullptr;
		}
		return &data[front];
	}

	//debug
	void debugPrintContents()
	{
		std::cout << "Cola: " << "[";
		for (size_t i = 0; i <= maxsize; i++)
		{
			std::cout << data[i] << " ";
		}
		std::cout << "] front: " << front << "rear: " << rear << std::endl;
	}
};

