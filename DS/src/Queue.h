#pragma once
#include <vector>
#include "List.h"

template <class T>
class GeneralizedQueue
{
public:
	virtual ~GeneralizedQueue() {}

	virtual void push(T val) = 0;
	void push(std::initializer_list<T> values)
	{
		for (auto it = values.begin(); it != values.end(); it++)
			push(*it);
	}
	virtual T pop() = 0;
	virtual bool empty() = 0;
};

enum QueueImpl
{
	STACK_IMPL_ARRAY = 0,
	STACK_IMPL_LIST,
	QUEUE_IMPL_ARRAY,
	QUEUE_IMPL_LIST
};

template <class T>
class StackImplArray : public GeneralizedQueue<T>
{
public:
	StackImplArray(size_t size) : maxSize(size), stack(new T[maxSize]) {}

	~StackImplArray()
	{
		delete[] stack;
	}

	bool empty()
	{
		return head == 0;
	}

	void push(T val)
	{
		if(head < maxSize)
		    stack[head++] = val;
	}

	T pop()
	{
		return stack[--head];
	}

private:
	size_t maxSize;
	T* stack;
	size_t head = 0;
};

template <class T>
class StackImplList : public GeneralizedQueue<T>
{
public:
	void push(T val)
	{
		stack.Add(val);
		head++;
	}

	bool empty()
	{
		return stack.Size() == 0;
	}

	T pop()
	{
		return stack.Remove(head--);
	}
private:
	List<T> stack;
	int head = -1;
};

template <class T>
class QueueImplArray : public GeneralizedQueue<T>
{
public:
	QueueImplArray(size_t size) : maxSize(size), queue(new T[maxSize]) {}

	~QueueImplArray()
	{
		delete[] queue;
	}

	void push(T val)
	{
		if (size < maxSize)
		{
			size++;
			if (last == maxSize)
				last = 0;

			queue[last++] = val;
		}
	}

	bool empty()
	{
		return size == 0;
	}

	T pop()
	{
		size--;
		if (first == maxSize)
			first = 0;

		return queue[first++];
	}
private:
	size_t maxSize;
	T* queue;
	size_t first = 0;
	size_t last = 0;
	size_t size = 0;
};

template <class T>
class QueueImplList : public GeneralizedQueue<T>
{
	~QueueImplList()
	{
		int dummy = 0; // for debug
	}
	void push(T val)
	{
		queue.Add(val);
	}

	bool empty()
	{
		return queue.Size() == 0;
	}

	T pop()
	{
		return queue.Remove(0);
	}
private:
	List<T> queue;
};

template <class T>
GeneralizedQueue<T>* createGeneralizedQueue(QueueImpl impl, size_t maxSize = 0)
{
	if (impl == STACK_IMPL_ARRAY)
		return new StackImplArray<T>(maxSize);

	if (impl == STACK_IMPL_LIST)
		return new StackImplList<T>();

	if (impl == QUEUE_IMPL_ARRAY)
		return new QueueImplArray<T>(maxSize);

	if (impl == QUEUE_IMPL_LIST)
		return new QueueImplList<T>();

	return nullptr;
}