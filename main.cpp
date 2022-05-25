#include <iostream>
#include "src/UserSorting.h"
#define PATH "../test_numbers.txt"

void AlgorithmSorted(int size);

int main() {
    try {
        std::cout << "TESTING N1 = 20000\n";
        AlgorithmSorted(20000);

        std::cout << "\nTESTING N2 = 50000\n";
        AlgorithmSorted(50000);

        std::cout << "TESTING N3 = 80000\n";
        AlgorithmSorted(80000);

        std::cout << "TESTING N4 = 110000\n";
        AlgorithmSorted(110000);
    }

    catch (std::string& ex) {
        std::cout << ex;
        return 1;
    }

    std::cout << "All testing completed...\n";

    return 0;
}

void AlgorithmSorted(int size) {
    UserSorting main_algorithm;

    try {
        std::cout << "\nBUBBLE SORT\n_____\n";
        main_algorithm.FillArray(std::string(PATH), size);
        main_algorithm.BubbleSort();
        main_algorithm.ClearArray();

        std::cout << "\nSHAKER SORT\n_____\n";
        main_algorithm.FillArray(std::string(PATH), size);
        main_algorithm.ShakerSort();
        main_algorithm.ClearArray();

        std::cout << "\nQUICK SORT\n_____\n";
        main_algorithm.FillArray(std::string(PATH), size);
        main_algorithm.QuickSort();
        main_algorithm.ClearArray();

        std::cout << "\nMERGE SORT\n_____\n";
        main_algorithm.FillArray(std::string(PATH), size);
        main_algorithm.MergeSort();
        main_algorithm.ClearArray();

        std::cout << "\nTest completed. Enter any character to continue..\n";
        getchar();
        system("clear");
    }

    catch (std::string &ex) {
        throw ex;
    }
}