#pragma once

#include <iostream>
#include "Iterable.h"
#include "Visitor.h"

#include <algorithm>

#define MIN_ARRAY_SIZE 8

using namespace std;

template <class T> class Stack: public Iterable<T>
{
private:
	T* array;
	int maxSize;
	int currentSize;

	template <class T> friend ostream& operator<< (ostream&, Stack<T> const&);

	template <class T> friend istream& operator>> (istream&, Stack<T>&);

	template <class T> friend void swap(Stack<T>&, Stack<T>&);

	void arrayIncrease()
	{
		maxSize *= 2;
		T* auxiliaryArray = new T[maxSize];

		for (int i = 0; i < currentSize; ++i)
		{
			auxiliaryArray[i] = array[i];
		}

		delete[] array;

		array = auxiliaryArray;
	}

	void arrayDecrease()
	{
		maxSize /= 2;
		T* auxiliaryArray = new T[maxSize];

		for (int i = 0; i < maxSize / 2; ++i)
		{
			auxiliaryArray[i] = array[i];
		}

		delete[] array;

		array = auxiliaryArray;
	}

public:
	Stack()
	{
		array = new T[MIN_ARRAY_SIZE];
		maxSize = MIN_ARRAY_SIZE;
		currentSize = 0;
	}

	Stack(initializer_list<T> list)
	{
		maxSize = max(MIN_ARRAY_SIZE, int(round(exp(ceil(log(list.size()) / log(2)) * log(2)))));
		array = new T[maxSize];
		currentSize = 0;

		for (auto item : list)
		{
			array[currentSize++] = item;
		}
	}

	Stack(Stack const& stack)
	{
		maxSize = stack.maxSize;
		array = new T[maxSize];
		currentSize = stack.currentSize;

		for (int i = 0; i < stack.currentSize; ++i)
		{
			array[i] = stack.array[i];
		}
	}

	Stack(Stack&& stack)
	{
		array = stack.array;
		stack.array = new T[MIN_ARRAY_SIZE];

		maxSize = stack.maxSize;
		stack.maxSize = MIN_ARRAY_SIZE;

		currentSize = stack.currentSize;
		stack.currentSize = 0;
	}

	~Stack()
	{
		delete[] array;
	}

	bool isEmpty() const
	{
		return !currentSize;
	}

	int size() const
	{
		return currentSize;
	}

	void clear()
	{
		delete[] array;

		array = new T[MIN_ARRAY_SIZE];
		maxSize = MIN_ARRAY_SIZE;
		currentSize = 0;
	}

	T top() const
	{
		if (isEmpty())
		{
			throw runtime_error("Error: wrong use of the method top\n");
		}

		return array[currentSize - 1];
	}

	void push(T const& value)
	{
		if (currentSize == maxSize)
		{
			arrayIncrease();
		}

		array[currentSize++] = value;
	}

	void pop()
	{
		if (isEmpty())
		{
			throw runtime_error("Error: wrong use of the method pop\n");
		}

		--currentSize;

		if ((4 * currentSize == maxSize) && (maxSize != MIN_ARRAY_SIZE))
		{
			arrayDecrease();
		}
	}

	Stack& operator= (Stack const& stack)
	{
		Stack auxiliaryStack(stack);
		swap(*this, auxiliaryStack);

		return *this;
	}

	Stack& operator= (Stack&& stack)
	{
		Stack auxiliaryStack = move(stack);
		swap(*this, auxiliaryStack);

		return *this;
	}

	Stack operator+ (Stack const& stack) const
	{
		Stack auxiliaryStack(*this);

		for (int i = 0; i < stack.currentSize; ++i)
		{
			auxiliaryStack.push(stack.array[i]);
		}

		return auxiliaryStack;
	}

	Stack& operator+= (Stack const& stack)
	{
		*this = *this + stack;

		return *this;
	}

	bool operator== (Stack const& stack) const
	{
		if (currentSize != stack.currentSize)
		{
			return false;
		}

		for (int i = 0; i < currentSize; ++i)
		{
			if (array[i] != stack.array[i])
			{
				return false;
			}
		}

		return true;
	}

	bool operator!= (Stack const& stack) const
	{
		return !(*this == stack);
	}

	Iterator<T>* createIterator() const override;

	void accept(Visitor<T>& visitor) const
	{
		visitor.visit(*this);
	}

	static T* getArray(Stack const& stack)
	{
		T* array = new T[stack.size()];

		for (int i = 0; i < stack.size(); ++i)
		{
			array[i] = stack.array[i];
		}

		return array;
	}
};

template <class T> ostream& operator<< (ostream& os, Stack<T> const& stack)
{
	for (int i = stack.currentSize - 1; i >= 0; --i)
	{
		os << stack.array[i] << " ";
	}

	os << endl;

	return os;
}

template <class T> istream& operator>> (istream& is, Stack <T>& stack)
{
	while (is.peek() != '\n')
	{
		T x;
		is >> x;

		if (is.fail())
		{
			throw runtime_error("Error: wrong input");
		}

		stack.push(x);
	}

	is.get();

	return is;
}

template <class T> void swap(Stack<T>& leftStack, Stack<T>& rightStack)
{
	swap(leftStack.array, rightStack.array);
	swap(leftStack.maxSize, rightStack.maxSize);
	swap(leftStack.currentSize, rightStack.currentSize);
}