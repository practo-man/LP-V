#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

#define SIZE 20

// Print Array
void printArray(const vector<int>& arr) {

    for (int num : arr)
        cout << num << " ";

    cout << endl;
}

// Sequential Bubble Sort
void bubbleSortSequential(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        for (int j = 0; j < n - i - 1; j++) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Parallel Bubble Sort
void bubbleSortParallel(vector<int>& arr) {

    int n = arr.size();

    for (int i = 0; i < n; i++) {

        // Even Phase
        #pragma omp parallel for
        for (int j = 0; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }

        // Odd Phase
        #pragma omp parallel for
        for (int j = 1; j < n - 1; j += 2) {

            if (arr[j] > arr[j + 1]) {

                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Generate Random Numbers
void generateRandom(vector<int>& arr) {

    for (int& x : arr)
        x = rand() % 100;
}

int main() {

    vector<int> arr(SIZE), temp;

    srand(time(0));

    generateRandom(arr);

    cout << "Original Array:" << endl;
    printArray(arr);

    double start, end;

    // Sequential Bubble Sort
    temp = arr;

    start = omp_get_wtime();

    bubbleSortSequential(temp);

    end = omp_get_wtime();

    cout << "\nSequential Bubble Sorted Array:" << endl;
    printArray(temp);

    cout << "Sequential Time: "
         << (end - start)
         << " sec" << endl;

    // Parallel Bubble Sort
    temp = arr;

    start = omp_get_wtime();

    bubbleSortParallel(temp);

    end = omp_get_wtime();

    cout << "\nParallel Bubble Sorted Array:" << endl;
    printArray(temp);

    cout << "Parallel Time: "
         << (end - start)
         << " sec" << endl;

    return 0;
}