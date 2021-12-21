#pragma once
#include "Queue.h"
#include <iostream>
#include <map>

template <class T>
struct TreeNode
{
	T data;
	TreeNode<T>* left;
	TreeNode<T>* right;
	bool internal;
};

template <class T>
class Tree
{
public:
	typedef TreeNode<T>* Link;

	Tree()
	{
		nodes = createGeneralizedQueue<Link>(QUEUE_IMPL_LIST);
	}

	virtual ~Tree()
	{
		if(root)
		    remove(root);

		delete nodes;
	}

	void construct(std::initializer_list<T> values)
	{
		for (auto it = values.begin(); it != values.end(); it++)
			add(*it);

		int dummy = 0;
	}

	void inOrder()
	{
		std::cout << "In order:\n";
		if(root)
		    inOrderImpl(root);

		std::cout << std::endl;
	}

	void preOrder()
	{
		std::cout << "Pre order:\n";
		GeneralizedQueue<Link>* stack = createGeneralizedQueue<Link>(STACK_IMPL_LIST);
		stack->push(root);
		while (!stack->empty())
		{
			Link node = stack->pop();
			if (node->internal)
			{
				std::cout << node->data << ", ";
				stack->push(node->right);
				stack->push(node->left);
			}
		}

		std::cout << std::endl;

		delete stack;
	}

	void levelOrder()
	{
		std::cout << "Level order:\n";
		GeneralizedQueue<Link>* stack = createGeneralizedQueue<Link>(QUEUE_IMPL_LIST);
		stack->push(root);
		while (!stack->empty())
		{
			Link node = stack->pop();
			if (node->internal)
			{
				std::cout << node->data << ", ";
				stack->push(node->left);
				stack->push(node->right);
			}
		}

		std::cout << std::endl;

		delete stack;
	}

	int count()
	{
		return countImpl(root);
	}

	int depth()
	{
		return depthImpl(root);
	}

protected:
	int depthImpl(Link node)
	{
		if (!node->internal) return 0;

		return std::max(depthImpl(node->left), depthImpl(node->right)) + 1;
	}

	int countImpl(Link node)
	{
		if (!node->internal) return 0;

		return countImpl(node->left) + countImpl(node->right) + 1;
	}

	void inOrderImpl(Link node)
	{
		if (!node->internal) return;

		inOrderImpl(node->left);
		std::cout << node->data << ", ";
		inOrderImpl(node->right);
	}

	void add(T data)
	{
		if (!root)
		{
			Link left = new TreeNode<T>();
			left->internal = false;

			Link right = new TreeNode<T>();
			right->internal = false;

			root = new TreeNode<T>{ data, left, right, true };
			nodes->push(root->left);
			nodes->push(root->right);
		}
		else
		{
			Link left = new TreeNode<T>();
			left->internal = false;

			Link right = new TreeNode<T>();
			right->internal = false;

			Link node = nodes->pop();
			node->data = data;
			node->internal = true;
			node->left = left;
			node->right = right;

			nodes->push(node->left);
			nodes->push(node->right);
		}
	}

	void remove(Link node)
	{
		if (node->left)
			remove(node->left);

		if (node->right)
			remove(node->right);

		delete node;
	}

	Link root = nullptr;
	GeneralizedQueue<Link>* nodes;
};

template <class T>
class TournamentTree : public Tree<T>
{
public:
	typedef typename Tree<T>::Link Link;

	TournamentTree(std::initializer_list<T> values)
	{
		this->root = createTournamentImpl(values, 0, values.size());
	}

private:
	Link createTournamentImpl(std::initializer_list<T>& values, size_t l, size_t r)
	{
		if (r - l == 1)
		{
			Link left = new TreeNode<T>();
			left->internal = false;

			Link right = new TreeNode<T>();
			right->internal = false;

			return new TreeNode<T>{ *(values.begin() + l), left, right, true };
		}

		size_t middle = (r - l) / 2;
		Link node = new TreeNode<T>{};
		Link left = createTournamentImpl(values, l, l + middle);
		Link right = createTournamentImpl(values, l + middle, r);

		node->data = std::max(left->data, right->data);
		node->left = left;
		node->right = right;
		node->internal = true;

		return node;
	}
};

template <class T>
class Graph
{
public:
	void Add(T first, T second)
	{
		auto it = matrix.find(first);
		if (it == matrix.end())
		{
			AdjRow row = new List<T>();
			matrix[first] = row;
		}

		it = matrix.find(second);
		if (it == matrix.end())
		{
			AdjRow row = new List<T>();
			matrix[second] = row;
		}

		AdjRow row = matrix[first];
		row->Add(second);

		row = matrix[second];
		row->Add(first);

		if(std::find(orderedNodes.begin(), orderedNodes.end(), first) == orderedNodes.end())
		    orderedNodes.push_back(first);

		if (std::find(orderedNodes.begin(), orderedNodes.end(), second) == orderedNodes.end())
			orderedNodes.push_back(second);
	}

	void depthFirst()
	{
		if (orderedNodes.size() > 0)
		{
			std::cout << "Depth-first: ";
			std::vector<T> visited;
			depthFirstImpl(orderedNodes[0], visited);
			std::cout << std::endl;
		}
	}

	void breadthFirst()
	{
		if (orderedNodes.size() > 0)
		{
			GeneralizedQueue<T>* queue = createGeneralizedQueue<T>(QUEUE_IMPL_LIST);
			std::cout << "Depth-first: ";
			std::vector<T> visited;
			queue->push(orderedNodes[0]);

			while (!queue->empty())
			{
				T val = queue->pop();
				if (std::find(visited.begin(), visited.end(), val) == visited.end())
				{
					visited.push_back(val);
					std::cout << val << ", ";

					AdjRow list = matrix[val];
					while (!list->Empty())
						queue->push(list->Next()->data);
				}
			}

			std::cout << std::endl;

			delete queue;
		}
	}

	void reset()
	{
		for (auto it = orderedNodes.begin(); it != orderedNodes.end(); it++)
		{
			AdjRow row = matrix[*it];
			row->Reset();
		}
	}

	void construct(std::initializer_list<std::tuple<T, T>> pairs)
	{
		for (auto it = pairs.begin(); it != pairs.end(); it++)
			Add(std::get<0>(*it), std::get<1>(*it));
	}

	void printAdjacencyMatrix()
	{
		for (auto it = orderedNodes.begin(); it != orderedNodes.end(); it++)
		{
			std::cout << *it << ": ";
			matrix[*it]->Print();
		}
	}
private:
	void depthFirstImpl(T val, std::vector<T>& visited)
	{
		if (std::find(visited.begin(), visited.end(), val) == visited.end())
		{
			visited.push_back(val);
			std::cout << val << ", ";

			AdjRow list = matrix[val];
			while (!list->Empty())
				depthFirstImpl(list->Next()->data, visited);
		}
	}

	typedef List<T>* AdjRow;
	typedef std::map<T, AdjRow> Adj;

	Adj matrix;
	std::vector<T> orderedNodes;
};
