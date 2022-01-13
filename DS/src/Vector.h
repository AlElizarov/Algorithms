#pragma once
#include <cstring>

template <class T>
class Vector
{
public:
    Vector()
    {
        sz = 0;
        capacity = 5;
        arr = new T[capacity];
    }

    ~Vector()
    {
        delete[] arr;
    }

    Vector(const Vector<T>& other)
    {
        sz = other.sz;
        capacity = other.capacity;

        arr = new T[capacity];
        for (int i = 0; i < sz; i++)
        {
            arr[i] = other.arr[i];
        }
    }

    int size()
    {
        return sz;
    }

    void swap(int lIdx, int rIdx)
    {
        T tmp = arr[lIdx];
        arr[lIdx] = arr[rIdx];
        arr[rIdx] = tmp;
    }

    T& operator[](int idx)
    {
        return arr[idx];
    }

    void push_back(T val)
    {
        if (sz == capacity)
        {
            T* tmp = arr;
            capacity *= 2;
            arr = new T[capacity];

            memcpy(arr, tmp, sz * sizeof(T));

            delete[] tmp;
        }

        arr[sz++] = val;
    }

    void removeLast()
    {
        if(sz > 0)
            sz--;
    }

private:
    T* arr;
    int sz;
    int capacity;
};
