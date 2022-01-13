#pragma once
#include <iostream>
#include "Vector.h"

template <class T>
class Heap
{
public:
    Heap() = default;

    Heap(const Heap<T>& other) :arr(other.arr) {}

    ~Heap()
    {
        int dummy = 0;
    }

    void insert(T val)
    {
        arr.push_back(val);
        heapifyUp();
    }

    void delMax()
    {
        if (arr.size() == 0) return;

        arr.swap(0, arr.size() - 1);
        arr.removeLast();

        heapifyDown();
    }

    int size()
    {
        return arr.size();
    }

    void construct(std::initializer_list<T> vals)
    {
        for (auto it = vals.begin(); it != vals.end(); it++)
            insert(*it);
    }

    void print()
    {
        std::cout << std::endl;
        for (int i = 0; i < arr.size(); i++)
        {
            std::cout << arr[i] << ", ";
        }
        std::cout << std::endl;
    }

    T* sort()
    {
        if (size() == 0) return nullptr;

        int sortedSize = size();
        T* sortedArr = new T[sortedSize];

        Heap<T> tmp = *this;

        while (sortedSize)
        {
            sortedArr[sortedSize - 1] = tmp.arr[0];
            tmp.delMax();
            sortedSize--;
        }

        return sortedArr;
    }

private:
    Vector<T> arr;

    void heapifyUp()
    {
        int currIdx = arr.size();
        int parentIdx = currIdx / 2;

        while (parentIdx > 0 && arr[currIdx - 1] > arr[parentIdx - 1])
        {
            arr.swap(currIdx - 1, parentIdx - 1);
            currIdx = parentIdx;
            parentIdx = currIdx / 2;
        }
    }

    void heapifyDown()
    {
        int currIdx = 1;
        int lChildIdx = currIdx * 2;
        int rChildIdx = currIdx * 2 + 1;

        int swapIdx = 0;
        while (true)
        {
            swapIdx = currIdx;

            if (arr.size() >= lChildIdx && arr[lChildIdx - 1] > arr[swapIdx - 1])
                swapIdx = lChildIdx;

            if (arr.size() >= rChildIdx && arr[rChildIdx - 1] > arr[swapIdx - 1])
                swapIdx = rChildIdx;

            if (swapIdx == currIdx)
                break;

            arr.swap(currIdx - 1, swapIdx - 1);
            currIdx = swapIdx;
            lChildIdx = currIdx * 2;
            rChildIdx = currIdx * 2 + 1;
        }
    }
};