#pragma once

template <class T> class Stack;

template <class T> class Visitor
{
public:
	virtual ~Visitor() = default;

	virtual void visit(Stack<T> const&) = 0;

	virtual T getValue() const = 0;
};