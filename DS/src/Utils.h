#pragma once
#include "List.h"
#include <vector>

void sieveErathosfen(int N);

int leaderArray(const List<int>& list, int gap);

enum Direction
{
	RIGHT = 0,
	LEFT
};

class Hanoi
{
public:
	void run(int n, Direction d);
private:
	void move(int n);
	void print();
	int find(int n);

	List<int> piles[3];

	bool initialized = false;
	int from = 0;
	int to = 1;

	int height = 0;
	Direction direction = RIGHT;
};

class Knapsak
{
public:
	Knapsak(std::initializer_list<int> w, std::initializer_list<int> c, int capacity);

	int solve();
private:
	int solveImpl(int c);

	std::vector<int> weights;
	std::vector<int> costs;
	int cap;

	std::vector<int> mem;
};

void ruller(int n);