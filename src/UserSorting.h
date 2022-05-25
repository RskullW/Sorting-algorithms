#pragma once

#include <iostream>
#include <string>

class UserSorting {
public:
    explicit UserSorting();
    ~UserSorting();

    void FillArray(std::string path, unsigned size);
    void ClearArray();

    void BubbleSort();
    void ShakerSort();
    void QuickSort();
    void MergeSort();

    template<class T> void Log(T user_message) const {
        std::cout << "LOG: " << user_message << '\n';
    }

private:
    void ReverseArray();

    void BubbleSortLocal();
    void ShakerSortLocal();
    void QuickSortLocal(int* array, int size);
    void MergeSortLocal();

private:

    unsigned m_size;
    float start_time;
    int *m_array;
};