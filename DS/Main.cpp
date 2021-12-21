#include <iostream>
#include "List.h"
#include "Utils.h"
#include "Queue.h"
#include "Tree.h"

void testQueue(QueueImpl impl, size_t maxSize = 0);

int main()
{
	std::cout << "=========Sieve=======\n";
	sieveErathosfen(100);
	std::cout << "\n\n\n";

	/*
	* LIST TRAIN
	*/
	{
		std::cout << "=========List fill=======\n";
		List<int> list;
		list.Add(5);
		list.Add(3);
		list.Add({ 4,7,9,10,3,12,26 });
		list.Print();
		std::cout << "\n\n\n";

		std::cout << "=========List recursion=======\n";
		list.PrintRecursive();
		std::cout << "\n\n\n";

		std::cout << "=========List revers=======\n";
		list.Revers();
		list.Print();
		std::cout << "\n\n\n";

		{
			std::cout << "=========Leader=======\n";
			List<int> tmp(list);
			std::cout << tmp.FindLeader(5);
			std::cout << "\n\n\n";
		}

		std::cout << "=========Leader array=======\n";
		std::cout << leaderArray(list, 5);
		std::cout << "\n\n\n";

		std::cout << "=========List sort=======\n";
		List<int>* sortedList = list.Sort();
		sortedList->Print();
		list.Print();
		delete sortedList;
		std::cout << "\n\n\n";
	}

	/*
	* QUEUE TRAIN
	*/
	{
		std::cout << "=========Stack Array impl=======\n";
		testQueue(STACK_IMPL_ARRAY, 100);

		std::cout << "=========Stack List impl=======\n";
		testQueue(STACK_IMPL_LIST);

		std::cout << "=========Queue Array impl=======\n";
		testQueue(QUEUE_IMPL_ARRAY, 8);

		std::cout << "=========Queue List impl=======\n";
		testQueue(QUEUE_IMPL_LIST);
	}

	/*std::cout << "=========Hanoi=======\n";
	Hanoi hanoi;
	hanoi.run(5, RIGHT);
	std::cout << "\n\n\n";*/

	{
		std::cout << "=========Ruller=======\n";
		ruller(4);
		std::cout << "\n\n\n";

		std::cout << "=========Knapsak=======\n";
		Knapsak knapsak({ 3,4,7,8,9 }, { 4,5,8,11,13 }, 16);
		std::cout << knapsak.solve();
		std::cout << "\n\n\n";
	}

	{
		std::cout << "=========Tree=======\n";
		{
			Tree<int> tree;
			tree.construct({ 8,4,5,2,3,1,6,1,0,8 });
			tree.inOrder();
			tree.preOrder();
			tree.levelOrder();
			std::cout << "Count number: " << tree.count() << std::endl;
			std::cout << "Depth: " << tree.depth() << std::endl << std::endl;
		}
		{
			std::cout << "Tournament: ";
			TournamentTree<int> tournament({ 3,5,9,7 });
			tournament.levelOrder();
			std::cout << "\n\n\n";
		}

		std::cout << "=========Graph=======\n";
		Graph<int> graph;
		graph.construct({ {4,2}, {4,6}, {4,7}, {4,3}, {2,8}, {3,9}, {8,9} });
		graph.printAdjacencyMatrix();
		graph.depthFirst();
		graph.reset();
		graph.breadthFirst();
		std::cout << "\n\n\n";
	}

	return 0;
}

void testQueue(QueueImpl impl, size_t maxSize)
{
	GeneralizedQueue<int>* gQueue = createGeneralizedQueue<int>(impl, maxSize);
	gQueue->push(20);
	gQueue->push(8);
	gQueue->push({ 2,7,34,21,4,7,90 });
	gQueue->pop();
	gQueue->pop();
	gQueue->push(30);
	gQueue->push(100);
	while (!gQueue->empty())
		std::cout << gQueue->pop() << ", ";

	std::cout << std::endl;
	gQueue->push(20);
	gQueue->push(8);
	gQueue->push({ 2,7,34,21,4,7,90 });
	while (!gQueue->empty())
		std::cout << gQueue->pop() << ", ";
	std::cout << "\n\n\n";
	delete gQueue;
}