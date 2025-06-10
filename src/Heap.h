#pragma once
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T> 
class Heap
{
protected:
	std::vector<T> data;

public:
	size_t Size() const 
	{
		return data.size();
	};
	
    Heap() {}

    void Insert(const T& element) 
    {
        data.push_back(element);
        std::push_heap(data.begin(), data.end(), std::less<>());
    }

    T Extract() 
    {
        if (IsEmpty()) std::cout << ("Heap vacío");
        std::pop_heap(data.begin(), data.end(), std::less<>());
        T max = data.back();
        data.pop_back();
        return max;
    }

    T Peek() const 
    {
        if (IsEmpty()) std::cout << ("Heap vacío");
        return data.front();
    }

    bool IsEmpty() const 
    {
        return data.empty();
    }

};

