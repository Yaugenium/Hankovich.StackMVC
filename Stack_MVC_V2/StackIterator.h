#pragma once

#include <iostream>
#include "Stack.h"

using namespace std;

template <class T> class StackIterator : public Iterator<T>
{
private:
	int current;
	const Stack<T>& stack;

public:
	StackIterator(Stack<T> const& stack) : stack(stack)
	{
		current = -1;
	}

	void first() override
	{
		current = stack.size() - 1;
	}

	void next() override
	{
		--current;
	}

	bool isDone() const override
	{
		return (current <= -1);
	}

	T currentItem() const override
	{
		if (current >= stack.size() || current < 0)
		{
			throw runtime_error("Error: use of an invalid iterator\n");
		}

		return  Stack<T>::getArray(stack)[current];
	}
};

template <class T> Iterator<T>* Stack<T>::createIterator() const
{
	return new StackIterator<T>(*this);
}