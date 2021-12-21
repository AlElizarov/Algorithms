#pragma once

#include <iostream>

template <class T>
struct Node
{
	T data;
	Node<T>* next;
};

template <class T>
class List
{
public:
	List() {}

	List(const List<T>& other)
	{
		for (size_t i = 0; i < other.size; i++)
			Add(other[i]);
	}

	~List()
	{
		while (first)
		{
			Node<T>* tmp = first;
			first = first->next;

			// Handle Circle list case
			if (tmp == first)
			{
				delete tmp;
				break;
			}

			delete tmp;
		}
	}

	void Add(T data)
	{
		Node<T>* node = new Node<T>{ data, nullptr };

		if (!head)
		{
			head = node;
			first = head;
		}

		if (tail)
			tail->next = node;

		tail = node;
		size++;
	}

	List<T>* Sort()
	{
		List<T>* res = new List<T>();

		if (head)
		{
			while (!Empty())
			{
				Node<T>* min = head;
				int count = 0;
				int minCnt = 0;

				Node<T>* it = head;
				while (it)
				{
					if (it->data < min->data)
					{
						min = it;
						minCnt = count;
					}

					it = it->next;
					count++;
				}

				res->Add(min->data);
				Remove(minCnt);
			}
		}

		return res;
	}

	size_t Size() const
	{
		return size;
	}

	void Add(std::initializer_list<T> list)
	{
		for (auto it = list.begin(); it != list.end(); it++)
			Add(*it);
	}

	Node<T>* Next()
	{
		Node<T>* tmp = head;
		if (head)
			head = head->next;

		return tmp;
	}

	void Reset()
	{
		head = first;
	}

	bool Empty()
	{
		return head == nullptr;
	}

	void Print() const
	{
		Node<T>* tmp = head;
		while (tmp)
		{
			std::cout << tmp->data << ", ";
			tmp = tmp->next;
		}

		std::cout << std::endl;
	}

	void PrintRecursive() const
	{
		PrintRecursiveImpl(head);
	}

	void Revers()
	{
		Node<T>* l = nullptr;
		Node<T>* r = nullptr;

		Node<T>* curr = head;
		tail = head;
		first = tail;

		while (curr)
		{
			head = r = curr;
			curr = curr->next;
			r->next = l;
			l = r;
			r = curr;
		}
	}

	T Remove(size_t idx)
	{
		if (idx == 0)
		{
			Node<T>* node = new Node<T>();
			node->next = head;
			return RemoveNext(node);
		}

		Node<T>* node = head;
		for (int i = 0; i < int(idx - 1) && node; i++)
			node = node->next;

		return RemoveNext(node);
	}

	T FindLeader(int gap)
	{
		MakeCircle();

		Node<T>* tmp = head;
		while (tmp && tmp != tmp->next)
		{
			for (int i = 2; i < gap; i++)
				tmp = tmp->next;

			if (!tmp->next)
				return -1;

			RemoveNext(tmp);
			tmp = tmp->next;
		}

		return tmp ? tmp->data : -1;
	}

	T operator[](size_t idx) const
	{
		Node<T>* tmp = head;
		for (size_t i = 0; i < idx; i++)
		{
			if (!tmp)
				return -1;

			tmp = tmp->next;
		}

		return tmp ? tmp->data : -1;
	}

private:
	Node<T>* head = nullptr;
	Node<T>* tail = nullptr;
	Node<T>* first = nullptr;

	size_t size = 0;

	void PrintRecursiveImpl(Node<T>* node) const
	{
		if (node)
		{
			PrintRecursiveImpl(node->next);
			std::cout << node->data << ", ";
		}
	}

	void MakeCircle()
	{
		if (tail)
			tail->next = head;
	}

	T RemoveNext(Node<T>* curr)
	{
		if (!curr)
			throw std::exception();

		T data;
		if (curr->next)
		{
			Node<T>* tmp = curr->next;
			curr->next = curr->next->next;

			if (tmp == head)
			{
				head = head->next;
				first = head;
			}

			if (tmp == tail)
				tail = curr;

			data = tmp->data;
			delete tmp;
		}
		else // delete head
		{
			data = head->data;
			Node<T>* tmp = head->next;
			delete head;
			head = tmp;
		}

		if (--size == 0)
		{
			head = nullptr;
			tail = nullptr;
			first = nullptr;
		}

		return data;
	}
};
