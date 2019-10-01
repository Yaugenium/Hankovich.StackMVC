#pragma once

template <class T> class Iterator
{
public:
	virtual ~Iterator() = default;

	virtual void first() = 0;

	virtual void next() = 0;

	virtual bool isDone() const = 0;

	virtual T currentItem() const = 0;
};