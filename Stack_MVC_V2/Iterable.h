#pragma once

#include "Iterator.h"

template <class T> class Iterable
{
public:
	virtual ~Iterable() = default;

	virtual Iterator<T>* createIterator() const = 0;
};