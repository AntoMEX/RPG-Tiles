#pragma once

template <typename T>
class Stack
{
private:
	T* data;
	size_t top;

public:
	size_t maxsize;

	//Constructor
	Stack(size_t _maxsize) 
	{
		maxsize = _maxsize;
		data = new T(maxsize);
		top = 0;
	}

	~Stack() 
	{
		delete[] data;
	}

	void push(T item) 
	{
		top++;
		if (top > maxsize)
		{
			std::cout << "Stack overflow" << std::endl;
		}
		else 
		{
			data[top - 1] = item;
		}
	}

	T pop() 
	{
		if (top > 0)
		{
			top--;
			return data[top];
		}
		//warning
		else 
		{
			std::cout << "Stack vacio" << std::endl;
			//return nullptr
			return T();
		}
	}

	T* peek() 
	{
		if (top > 0) 
		{
			return &data[top - 1];
		}
		else 
		{
			return nullptr;
		}
	}

	bool IsEmpty() 
	{
		//si top es cero, quiere decir que no hay elementos
		return top == 0;
	}

	size_t size() 
	{
		return top;
	}
};

