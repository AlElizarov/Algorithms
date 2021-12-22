#include <iostream>
#include <algorithm>
#include "Sort.h"

void trainSort(Alg algo);
void listSort(SortAlgorithm algo);

struct Res
{
	Alg alg;
	bool res;
};

std::vector<Res> results;

int main()
{
	std::cout << "==============Selection sort============\n";
	trainSort({SELECTION_SORT, "Selection: ", false});
	std::cout << "\n\n\n";

	std::cout << "==============Bubble sort============\n";
	trainSort({BUBBLE_SORT, "Bubble: ", true});
	std::cout << "\n\n\n";

	std::cout << "==============Insertion sort============\n";
	trainSort({INSERTION_SORT, "Insertion: ", true});
	std::cout << "\n\n\n";

	std::cout << "==============Shell sort============\n";
	trainSort({SHELL_SORT, "Shell: ", false});
	std::cout << "\n\n\n";

	std::cout << "==============Quick sort============\n";
	trainSort({QUICK_SORT, "Quicksort: ", false});
	std::cout << "\n\n\n";

	std::cout << "==============Quick sort non recursive============\n";
	trainSort({QSORT_NON_RECURSIVE, "Qsort non recursive: ", false});
	std::cout << "\n\n\n";

	std::cout << "==============Merge sort============\n";
	trainSort({MERGE_SORT, "Merge sort: ", true});
	std::cout << "\n\n\n";

	std::cout << "==============Merge sort non recursive============\n";
	trainSort({MERGE_SORT_NON_RECURSIVE, "Merge sort non recursive: ", true});
	std::cout << "\n\n\n";

	std::cout << "==============List sort============\n";
	trainSort({ LIST_SORT, "List sort: ", true });
	std::cout << "\n\n\n";

	std::cout << "==============K statistics============\n";
	trainSort({K_STATISTICS, "", false});
	std::cout << "\n\n\n";

	std::cout << "==============Linear sort============\n";
	int arr[] = { 2,4,5,3,1,1,0,2,0 };
	size_t size = sizeof(arr) / sizeof(int);
	Sort::linearSort(&arr[0], size);
	for (size_t i = 0; i < size; i++)
		std::cout << arr[i] << ", ";
	std::cout << "\n\n\n";

	// Print results
	std::cout << std::endl << std::endl;
	for (int i = 0; i < results.size(); i++)
		std::cout << results[i].alg.text << (results[i].res ? "TRUE" : "FALSE") << std::endl;

	return 0;
}

void kStatistics(size_t size, Index<int>* indexes, Method m)
{
	int res = Sort::kStatistic(size, indexes, 2, m);
	std::cout << "2th statistics = " << res << std::endl;

	res = Sort::kStatistic(size, indexes, 3, m);
	std::cout << "3th statistics = " << res << std::endl;

	res = Sort::kStatistic(size, indexes, 5, m);
	std::cout << "5th statistics = " << res << std::endl;

	res = Sort::kStatistic(size, indexes, 8, m);
	std::cout << "8th statistics = " << res << std::endl;
}

void listSort(SortAlgorithm algo)
{
	List<int> list;
	list.Add({ 2, 4, 5, 3, 1, 1, 0, 2, 0 });
	std::cout << "List before sort:\n";
	list.Print();

	List<int>* sortedList = nullptr;
	switch (algo)
	{
	case SELECTION_SORT:
		sortedList = list.Sort();
		break;
	case MERGE_SORT:
		sortedList = list.MergeSort();
		break;
	}

	if (sortedList)
	{
		std::cout << "List after sort:\n";
		sortedList->Print();
		delete sortedList;
	}
}

void trainSort(Alg algo)
{
	// Initialization
	SortingElement<int> elements[] =
	{
		{4, {"John", 26}}, // 0
		{4, {"Kris", 76}}, // 1
		{2, {"Alex", 20}}, // 2
		{1, {"Smith", 33}}, // 3
		{1, {"Fred", 17}}, // 4  
		{1, {"Oleg", 17}}, // 5
		{5, {"Sean", 43}}, // 6
		{4, {"Eva", 26}},  // 7
		{7, {"Arnold", 65}}, // 8
		{3, {"Bred", 40}}, // 9
		{4, {"Julia", 45}}, // 10
		{12, {"Jan", 21}}, // 11
		{12, {"Kler", 41}}, // 12
		{5, {"Augusto", 40}}, // 13
		{6, {"Kate", 18}} // 14
	};

	int constexpr size = sizeof(elements) / sizeof(SortingElement<int>);
	SortingElement<int> ref[size];
	std::copy(std::begin(elements), std::end(elements), std::begin(ref));

	SortingElement<int> ref_sort[size];
	std::copy(std::begin(elements), std::end(elements), std::begin(ref_sort));
	std::sort(std::begin(ref_sort), std::end(ref_sort));

	Index<int>* indexes = new Index<int>[size];
	for (int i = 0; i < size; i++)
	{
		indexes[i].originalKey = elements[i].key;
		indexes[i].orderedKey = i;
	}

	// K statistics
	if (algo.alg == K_STATISTICS)
	{
		std::cout << "Recursion:\n";
		kStatistics(size, indexes, RECURSION);

		std::cout << "Stack:\n";
		kStatistics(size, indexes, STACK);

		return;
	}

	// List sort
	if (algo.alg == LIST_SORT)
	{
		std::cout << "\nSelection sort:\n";
		listSort(SELECTION_SORT);
		std::cout << "\nMerge sort:\n";
		listSort(MERGE_SORT);

		return;
	}

	// Sorting
	std::cout << "Before sort:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << elements[i] << std::endl;

	std::cout << "Indexed:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << elements[indexes[i].orderedKey] << std::endl;

	results.push_back({ algo, true });

	switch (algo.alg)
	{
	case SELECTION_SORT:
		Sort::selectionSort(size, indexes);
		break;
	case BUBBLE_SORT:
		Sort::bubbleSort(size, indexes);
		break;
	case INSERTION_SORT:
		Sort::insertionSort(size, indexes);
		break;
	case SHELL_SORT:
		Sort::shellSort(size, indexes);
		break;
	case QUICK_SORT:
		Sort::quickSort(size, indexes, RECURSION);
		break;
	case QSORT_NON_RECURSIVE:
		Sort::quickSort(size, indexes, STACK);
		break;
	case MERGE_SORT:
		Sort::mergeSort(size, indexes, RECURSION);
		break;
	case MERGE_SORT_NON_RECURSIVE:
		Sort::mergeSort(size, indexes, STACK);
		break;
	}
	std::cout << "\n\n\n";

	std::cout << "After sort:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << elements[i] << std::endl;

	// Verify results
	if (algo.stable)
	{
		if (!std::equal(std::begin(elements), std::end(elements), std::begin(ref), &compareStable<int>))
			results[results.size() - 1].res = false;
	}
	else
	{
		if (!std::equal(std::begin(elements), std::end(elements), std::begin(ref)))
			results[results.size() - 1].res = false;
	}

	std::cout << "Indexed:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << elements[indexes[i].orderedKey] << std::endl;

	Sort::inPlaceSort(&elements[0], size, indexes);
	std::cout << "\n\n\n";

	std::cout << "In-place sort:" << std::endl;
	for (int i = 0; i < size; i++)
		std::cout << elements[i] << std::endl;

	if (algo.stable)
	{
		if (!std::equal(std::begin(elements), std::end(elements), std::begin(ref_sort), &compareStable<int>))
			results[results.size() - 1].res = false;
	}
	else
	{
		if (!std::equal(std::begin(elements), std::end(elements), std::begin(ref_sort)))
			results[results.size() - 1].res = false;
	}
}