#include <vector>
#include <iostream>
#include <thread>
#include "Utils.h"

struct ArrayNode
{
	int data;
	size_t next;
};

void sieveErathosfen(int N)
{
	int* sieve = new int[N];

	for (int i = 0; i < N; i++)
		sieve[i] = 1;

	for (int i = 2; i < N; i++)
	{
		for (int j = i; j < N; j += i)
		{
			if (i != j)
				sieve[j] = 0;
		}
	}

	for (int i = 0, cnt = 0; i < N; i++)
	{
		if (sieve[i])
		{
			std::cout << i << ", ";
			cnt++;
		}

		if (sieve[i] && cnt % 10 == 0)
			std::cout << std::endl;
	}
}

int leaderArray(const List<int>& list, int gap)
{
	std::vector<ArrayNode> arr;
	for (size_t i = 0; i < list.Size() - 1; i++)
		arr.push_back({ list[i], i + 1 });

	arr.push_back({ list[list.Size() - 1], 0 });

	size_t current = 0;
	size_t next = arr[current].next;

	while (current != next)
	{
		for (int i = 2; i < gap; i++)
		{
			current = next;
			next = arr[current].next;
		}

		current = arr[current].next = arr[next].next;
		next = arr[current].next;
	}

	return arr[current].data;
}

void Hanoi::run(int n, Direction d)
{
	if (!initialized)
	{
		initialized = true;
		for (int i = n; i > 0; i--)
			piles[0].Add(i);

		if (d == LEFT)
		{
			from = 0;
			to = 2;
		}

		height = n;
		direction = d;

		print();
	}

	if (n == 0) return;

	run(n - 1, direction);
	move(n);
	run(n - 1, direction);
}

void Hanoi::move(int n)
{
	if (n == 1)
	{
		int element = piles[from].Remove(piles[from].Size() - 1);
		piles[to].Add(element);

		if (direction == RIGHT)
		{
			if (++from == 3)
				from = 0;

			if (++to == 3)
				to = 0;
		}
		else
		{
			if (--from == -1)
				from = 2;

			if (--to == -1)
				to = 2;
		}
	}
	else
	{
		int current = find(n);
		int small = find(1);

		int free = -1;
		for (int i = 0; i < 3; i++)
		{
			if (i != current && i != small)
				free = i;
		}

		int element = piles[current].Remove(piles[current].Size() - 1);
		piles[free].Add(element);
	}

	print();
}

int Hanoi::find(int n)
{
	for (int pile = 0; pile < 3; pile++)
	{
		for (int i = 0; i < piles[pile].Size(); i++)
			if (piles[pile][i] == n)
				return pile;
	}

	return -1;
}

void Hanoi::print()
{
	for (int i = height; i > 0; i--)
	{
		for (int pile = 0; pile < 3; pile++)
		{
			if (piles[pile].Size() >= i)
				std::cout << piles[pile][(size_t)i - 1];
			else
				std::cout << "|";
			std::cout << "     ";
		}

		std::cout << std::endl;
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));

	std::cout << "\n\n\n\n";
}

void ruller(int n)
{
	if (n == 0)
		return;

	ruller(n - 1);
	std::cout << n << " ";
	ruller(n - 1);
}

Knapsak::Knapsak(std::initializer_list<int> w, std::initializer_list<int> c, int capacity)
	: weights(w), costs(c), cap(capacity), mem(cap + 1, -1)
{ }

int Knapsak::solve()
{
	return solveImpl(cap);
}

int Knapsak::solveImpl(int c)
{
	if (mem[c] > -1)
		return mem[c];

	int max = 0;
	int sum = 0;
	for (int i = 0; i < weights.size(); i++)
	{
		if (c - weights[i] < 0) continue;

		sum = costs[i] + solveImpl(c - weights[i]);
		if (sum > max)
			max = sum;
	}

	mem[c] = max;
	return max;
}