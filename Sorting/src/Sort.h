#pragma once
#include <string>
#include <vector>
#include <tuple>
#include "Queue.h"
#include "Heap.h"

template <class T>
struct Index
{
	T originalKey;
	T orderedKey;

	bool operator== (const Index& other)
	{
		return originalKey == other.originalKey;
	}

	bool operator> (const Index& other)
	{
		return originalKey > other.originalKey;
	}
};

struct Person
{
	std::string name;
	int age;

	bool operator== (const Person& other)
	{
		return age == other.age && name == other.name;
	}
};

enum SortAlgorithm
{
	SELECTION_SORT = 0,
	BUBBLE_SORT,
	INSERTION_SORT,
	SHELL_SORT,
	QUICK_SORT,
	QSORT_NON_RECURSIVE,
	MERGE_SORT,
	MERGE_SORT_NON_RECURSIVE,
	LIST_SORT,
	HEAP_SORT,
	K_STATISTICS
};

enum Method
{
	RECURSION = 0,
	STACK
};

struct Alg
{
	SortAlgorithm alg;
	const char* text;
	bool stable;
};

template <class T>
struct SortingElement
{
	T key;
	Person person;

	friend std::ostream& operator <<(std::ostream& o, const SortingElement<T> e)
	{
		o << e.key << ": " << e.person.name << ", " << e.person.age;
		return o;
	}

	bool operator< (const SortingElement& other)
	{
		return key < other.key;
	}

	bool operator== (const SortingElement& other)
	{
		return key == other.key;
	}
};

template <class T>
bool compareStable(SortingElement<T>& a, const SortingElement<T>& b)
{
	return a.key == b.key && a.person == b.person;
}

class Sort
{
public:
	template <class T>
	static void selectionSort(size_t size, Index<T>* indexes)
	{
		for (int i = 0; i < size - 1; i++)
		{
			int min = i;
			for (size_t j = i; j < size; j++)
				if (indexes[j].originalKey < indexes[min].originalKey)
					min = j;

			swap(indexes[i], indexes[min]);
		}
	}

	template <class T>
	static void bubbleSort(size_t size, Index<T>* indexes)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = size - 1; j > i; j--)
				if (indexes[j].originalKey < indexes[j - 1].originalKey)
					swap(indexes[j], indexes[j - 1]);
	}

	template <class T>
	static void insertionSort(size_t size, Index<T>* indexes)
	{
		T min = indexes[0].originalKey;
		size_t minIdx = 0;
		for (size_t i = 1; i < size; i++)
		{
			if (min > indexes[i].originalKey)
			{
				min = indexes[i].originalKey;
				minIdx = i;
			}
		}
		swap(indexes[0], indexes[minIdx]);

		for (int i = 1; i < size; i++)
		{
			int j = i;
			T origKey = indexes[j].originalKey;
			while (origKey < indexes[j - 1].originalKey)
			{
				swap(indexes[j], indexes[j - 1]);
				j--;
			}
		}
	}

	template <class T>
	static void shellSort(size_t size, Index<T>* indexes)
	{
		int N = 1;
		while (N < size)
			N = N * 3 + 1;

		N /= 3;

		while (N > 0)
		{
			for (int i = 0; i < size - N; i++)
			{
				for (int j = i + N; j >= N; j -= N)
				{
					if (indexes[j].originalKey < indexes[j - N].originalKey)
						swap(indexes[j], indexes[j - N]);
				}
			}

			N /= 3;
		}
	}

	template <class T>
	static void heapSort(size_t size, Index<T>* indexes)
	{
		Heap<Index<T>> heap;
		for (size_t i = 0; i < size; i++)
			heap.insert(indexes[i]);

		Index<T>* tmp = heap.sort();

		for (size_t i = 0; i < size; i++)
			indexes[i] = tmp[i];

		delete[] tmp;
	}

	template <class T>
	static void inPlaceSort(SortingElement<T>* arr, size_t size, Index<T>* indexes)
	{
		for (size_t i = 0; i < size; i++)
		{
			T key = arr[i].key;
			T current = i;
			while (key != indexes[current].originalKey)
			{
				T order = indexes[current].orderedKey;
				swap(arr[current], arr[order]);

				indexes[current].orderedKey = current;

				for (int j = 0; j < size; j++)
				{
					if (indexes[j].orderedKey == current)
						indexes[j].orderedKey = order;
				}

				current = order;
			}
		}
	}

	static void linearSort(int* arr, size_t size)
	{
		int* counts = new int[size + 1];
		for (size_t i = 0; i < size + 1; i++)
			counts[i] = 0;

		for (size_t i = 0; i < size; i++)
			counts[arr[i] + 1]++;

		for (size_t i = 1; i < size; i++)
			counts[i] += counts[i - 1];

		int* tmp = new int[size];
		for (size_t i = 0; i < size; i++)
			tmp[counts[arr[i]]++] = arr[i];

		for (size_t i = 0; i < size; i++)
			arr[i] = tmp[i];
	}

	template <class T>
	static T kStatistic(size_t size, Index<T>* indexes, int k, Method m)
	{
		if(m == RECURSION)
		    return kStatisticImpl(0, size - 1, indexes, k);

		int left = 0;
		int right = size - 1;
		int part = partition(indexes, left, right);

		while (k != part)
		{
			if (k < part)
				right = part - 1;
			else
				left = part + 1;

			part = partition(indexes, left, right);
		}

		return indexes[part].originalKey;
	}

	template <class T>
	static void quickSort(size_t size, Index<T>* indexes, Method m)
	{
		if (m == RECURSION)
			quickSortImpl(0, size - 1, indexes);
		else
			quickSortNonReqursive(size, indexes);
	}

	template <class T>
	static void mergeSort(size_t size, Index<T>* indexes, Method m)
	{
		Index<T>* tmp = new Index<T>[size];

		if(m == RECURSION)
		    mergeSortImpl(0, size - 1, indexes, tmp);
		else
			mergeSortNonRecursive(size, indexes, tmp);

		delete[] tmp;
	}

private:
	template <class T>
	static void swap(T& first, T& second)
	{
		if (first == second)
			return;

		T tmp = first;
		first = second;
		second = tmp;
	}

	template <class T>
	static void mergeSortNonRecursive(size_t size, Index<T>* indexes, Index<T>* tmp)
	{
		int i;
		for (i = 2; i < size; i *= 2)
		{
			int j;
			for (j = i; j < size; j += i)
			{
				int left = j - i;
				int right = j - 1;
				merge(left, right, (left + (right - left) / 2), indexes, tmp);
			}

			int left = j - i;
			int right = size - 1;
			merge(left, right, (left + i / 2 - 1), indexes, tmp);
		}

		merge(0, size - 1, (i / 2 - 1), indexes, tmp);
	}

	template <class T>
	static void mergeSortImpl(int left, int right, Index<T>* indexes, Index<T>* tmp)
	{
		if (left == right) return;

		int median = left + (right - left) / 2;
		mergeSortImpl(left, median, indexes, tmp);
		mergeSortImpl(median + 1, right, indexes, tmp);

		merge(left, right, median, indexes, tmp);
	}

	template <class T>
	static void merge(int left, int right, int median, Index<T>* indexes, Index<T>* tmp)
	{
		int tmp_left_bound = left;
		for (int i = left; i <= median; i++)
			tmp[tmp_left_bound++] = indexes[i];

		//sentinel
		for (int j = right; j > median; j--)
			tmp[tmp_left_bound++] = indexes[j];

		int i, j, k;
		for (i = left, j = right, k = i; i <= median && j > median; k++)
		{
			if (tmp[i].originalKey <= tmp[j].originalKey)
				indexes[k] = tmp[i++];
			else
				indexes[k] = tmp[j--];
		}

		if(i > median)
			while(k <= right)
				indexes[k++] = tmp[j--];
		else
			while (k <= right)
				indexes[k++] = tmp[i++];
	}

	template <class T>
	static T kStatisticImpl(int left, int right, Index<T>* indexes, int k)
	{
		int part = partition(indexes, left, right);

		if (k == part)
			return indexes[part].originalKey;
		else if (k < part)
			return kStatisticImpl(left, part - 1, indexes, k);

		return kStatisticImpl(part + 1, right, indexes, k);
	}

	template <class T>
	static void quickSortImpl(int left, int right, Index<T>* indexes)
	{
		if (left >= right)
			return;

		int part = partition(indexes, left, right);

		// 3 way qsort. Left part
		int small = part - 1;
		int left_tmp = left;
		while (indexes[left_tmp].originalKey == indexes[part].originalKey && left_tmp < small)
			swap(indexes[left_tmp++], indexes[small--]);

		// 3 way qsort. Right part
		int large = part + 1;
		int right_tmp = right - 1;
		while (indexes[right_tmp].originalKey == indexes[part].originalKey && right_tmp > large)
			swap(indexes[right_tmp--], indexes[large++]);

		quickSortImpl(left, part - 1, indexes);
		quickSortImpl(part + 1, right, indexes);
	}

	template <class T>
	static int partition(Index<T>* indexes, int left, int right)
	{
		// select median from 3 elements
		int median = (left + right) / 2;
		if (indexes[left].originalKey > indexes[median].originalKey)
			swap(indexes[left], indexes[median]);

		if (indexes[left].originalKey > indexes[right].originalKey)
			swap(indexes[left], indexes[right]);

		if (indexes[median].originalKey < indexes[right].originalKey)
			swap(indexes[median], indexes[right]);

		// get partition element
		int j = right - 1;
		int i = left;
		T elem = indexes[right].originalKey;

		int small = left; // for 3-way qsort
		int large = right - 1; // for 3-way qsort
		for(;;)
		{
			while (indexes[i].originalKey < elem) i++;
			while (indexes[j].originalKey > elem && j >= left) j--;
			if (i >= j) break;
			swap(indexes[i++], indexes[j--]);

			// 3-way sorting. Left part
			if (indexes[i].originalKey == elem)
				swap(indexes[i], indexes[small++]);

			// 3-way sorting. Right part
			if (indexes[j].originalKey == elem)
				swap(indexes[i], indexes[large--]);
		}
		swap(indexes[i], indexes[right]);

		return i;
	}

	template <class T>
	static void quickSortNonReqursive(size_t size, Index<T>* indexes)
	{
		GeneralizedQueue<std::tuple<int, int>>* stack = createGeneralizedQueue<std::tuple<int, int>>(STACK_IMPL_LIST);
		stack->push({ 0, size - 1 });

		while (!stack->empty())
		{
			std::tuple<int, int> bounds = stack->pop();

			int left = std::get<0>(bounds);
			int right = std::get<1>(bounds);

			if (left >= right)
				continue;

			int part = partition(indexes, left, right);

			std::tuple<int, int> arr1 = { left, part - 1 };
			std::tuple<int, int> arr2 = { part + 1, right };

			if (part < (left + right) / 2)
				stack->push({ arr2, arr1 });
			else
				stack->push({ arr1, arr2 });
		}

		delete stack;
	}
};
