#include "UserSorting.h"
#include "fstream"
#include <ctime>

UserSorting::UserSorting() {
    m_size = 0;
    start_time = 0.f;
}

UserSorting::~UserSorting() {
    if (m_size != 0) {
        delete[] m_array;
    }

}

void UserSorting::FillArray(std::string path, unsigned size) {
    if (m_size > 0) {
        throw std::string("The array has already been filled. Please clear the array before filling...");
    }

    std::ifstream file;

    file.open(path.c_str());

    if (file.eof() || !file.is_open()) {
        throw std::string("The file does not exist or there are no entries in the file. Please check the path: ") + path;
    }

    m_array = new int[size];

    start_time = clock();

    while (!file.eof() && m_size != size) {
        file >> m_array[m_size++];
    }

    Log("Time spent filling the array = " + std::to_string((clock()-start_time)/1000.0f )+ " second");

    file.close();
}

void UserSorting::ClearArray() {
    if (m_array == 0) {
        std::cout << "Array \"m_array\" is empty\n";
        return;
    }

    m_size = 0;

    delete [] m_array;
}

void UserSorting::ReverseArray() {
    for (int i = 0; i < m_size/2; ++i) {
        std::swap(m_array[i], m_array[m_size-i-1]);
    }
}

void UserSorting::BubbleSort() {
    if (m_size == 0) {
        throw std::string("Array is empty");
    }

    start_time = clock();
    BubbleSortLocal();
    Log("Test Bubble-1 \"Unordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    start_time = clock();
    BubbleSortLocal();
    Log("Test Bubble-2 \"Ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    ReverseArray();

    start_time = clock();
    BubbleSortLocal();
    Log("Test Bubble-3 \"Reverse ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));
}

void UserSorting::ShakerSort() {
    if (m_size == 0) {
        throw std::string("Array is empty");
    }

    start_time = clock();
    ShakerSortLocal();
    Log("Test Shaker-1 \"Unordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    start_time = clock();
    ShakerSortLocal();
    Log("Test Shaker-2 \"Ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    ReverseArray();

    start_time = clock();
    ShakerSortLocal();
    Log("Test Shaker-3 \"Reverse ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));
}

void UserSorting::QuickSort() {
    if (m_size == 0) {
        throw std::string("Array is empty");
    }

    start_time = clock();
    QuickSortLocal(m_array, m_size);
    Log("Test Quick-1 \"Unordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    start_time = clock();
    QuickSortLocal(m_array, m_size);
    Log("Test Quick-2 \"Ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    ReverseArray();

    start_time = clock();
    QuickSortLocal(m_array, m_size);
    Log("Test Quick-3 \"Reverse ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));
}

void UserSorting::MergeSort() {
    if (m_size == 0) {
        throw std::string("Array is empty");
    }

    start_time = clock();
    QuickSortLocal(m_array, m_size);
    Log("Test Merge-1 \"Unordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    start_time = clock();
    QuickSortLocal(m_array, m_size);
    Log("Test Merge-2 \"Ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));

    ReverseArray();

    start_time = clock();
    QuickSortLocal(m_array, m_size);
    Log("Test Merge-3 \"Reverse ordered array\", time(second) = " + std::to_string((clock() - start_time) / 1000.0));
}

void UserSorting::BubbleSortLocal() {
    for (int i = 0; i < m_size-1; ++i) {
        for (int j = i+1; j < m_size; ++j) {
            if (*(m_array+i) > *(m_array + j)) {
                std::swap(*(m_array+i), *(m_array+j));
            }
        }
    }
}

void UserSorting::ShakerSortLocal() {
    int j, k = m_size-1, left = 1, right = m_size-1, x;

    do
    {
        for (j=right; j>=left; j--) {
            if (m_array[j - 1] > m_array[j]) {
                x = m_array[j - 1];
                m_array[j - 1] = m_array[j];
                m_array[j] = x;
                k = j;
            }
        }

        left = k+1;

        for (j=left; j<=right; j++) {
            if (m_array[j - 1] > m_array[j]) {
                x = m_array[j - 1];
                m_array[j - 1] = m_array[j];
                m_array[j] = x;
                k = j;
            }
        }

        right = k-1;
    } while (left<right);

}

void UserSorting::QuickSortLocal(int* array, int size) {
    int x = array[size/2], i = 0, j = size -1, w;

    do
    {
        while (array[i]<x) {
            i++;
        }

        while (x<array[j]) {
            j--;
        }

        if (i<=j) {
            w = array[i];

            array[i] = array[j];
            array[j] = w;

            i++;
            j--;
        }
    } while (i<j);

    if (j>0) {
        QuickSortLocal(array, j + 1);
    }

    if (i<size-1) {
        QuickSortLocal(array + i, size - i);
    }
}

void UserSorting::MergeSortLocal() {
    char flag = 0, sorted = 0;

    int split;
    int last, end, i, *p=m_array, *tmp, pos1, pos2, pos3;

    tmp = (int*) malloc (m_size*sizeof(int));
    do {
        end = m_size; pos2 = pos3 = 0;

        do {
            p += pos2; end = m_size - pos3;

            for (split=1; split < end && p[split-1] <= p[split]; split++);

            if (split == m_size) {
                sorted = 1 ; break;
            }

            pos1 = 0;
            pos2 = split;

            while ( pos1 < split && pos2 < end ) {

                if (p[pos1] < p[pos2]) {
                    tmp[pos3++] = p[pos1++];
                }

                else {
                    tmp[pos3++] = p[pos2++];
                    if (p[pos2] < p[pos2-1]) break;
                }

            }

            while ( pos2 < end && tmp[pos3-1]<=p[pos2] ) {
                tmp[pos3++] = p[pos2++];
            }

            while ( pos1 < split ) {
                tmp[pos3++] = p[pos1++];
            }
        }

        while (pos3 < m_size );

        if (sorted) {
            break;
        }

        p = tmp;
        tmp = m_array;
        m_array = p;
        flag = !flag;
    }

    while (split<m_size);

    if (flag) {

        for (pos1 = 0; pos1 < m_size; pos1++) {
            tmp[pos1] = m_array[pos1];
        }

        free (m_array);
    }

    else {
        free(tmp);
    }
}