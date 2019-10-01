#pragma once

#include <iostream>
#include "Stack.h"

using namespace std;

template <class T> class StackVisitor : public Visitor<T>
{
private:
	T sum;
public:
	StackVisitor() : sum(0) {};

	void visit(Stack<T> const& stack) override
	{
		for (int i = stack.size() - 1; i >= 0; --i)
		{
			sum += Stack<T>::getArray(stack)[i];
		}
	}

	T getValue() const override
	{
		return sum;
	}
};