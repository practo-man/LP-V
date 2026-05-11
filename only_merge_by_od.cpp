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

// Merge Function
void merge(vector<int>& arr, int l, int m, int r) {

    vector<int> left(arr.begin() + l,
                     arr.begin() + m + 1);

    vector<int> right(arr.begin() + m + 1,
                      arr.begin() + r + 1);

    int i = 0;
    int j = 0;
    int k = l;

    while (i < left.size() &&
           j < right.size()) {

        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < left.size())
        arr[k++] = left[i++];

    while (j < right.size())
        arr[k++] = right[j++];
}

// Sequential Merge Sort
void mergeSortSequential(vector<int>& arr,
                         int l,
                         int r) {

    if (l < r) {

        int m = (l + r) / 2;

        mergeSortSequential(arr, l, m);

        mergeSortSequential(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// Parallel Merge Sort
void mergeSortParallel(vector<int>& arr,
                       int l,
                       int r,
                       int depth) {

    if (l < r) {

        int m = (l + r) / 2;

        if (depth <= 0) {

            mergeSortSequential(arr, l, m);

            mergeSortSequential(arr,
                                m + 1,
                                r);
        }
        else {

            #pragma omp parallel sections
            {
                #pragma omp section
                mergeSortParallel(arr,
                                  l,
                                  m,
                                  depth - 1);

                #pragma omp section
                mergeSortParallel(arr,
                                  m + 1,
                                  r,
                                  depth - 1);
            }
        }

        merge(arr, l, m, r);
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

    // Sequential Merge Sort
    temp = arr;

    start = omp_get_wtime();

    mergeSortSequential(temp,
                        0,
                        SIZE - 1);

    end = omp_get_wtime();

    cout << "\nSequential Merge Sorted Array:" << endl;
    printArray(temp);

    cout << "Sequential Time: "
         << (end - start)
         << " sec" << endl;

    // Parallel Merge Sort
    temp = arr;

    start = omp_get_wtime();

    mergeSortParallel(temp,
                      0,
                      SIZE - 1,
                      4);

    end = omp_get_wtime();

    cout << "\nParallel Merge Sorted Array:" << endl;
    printArray(temp);

    cout << "Parallel Time: "
         << (end -start)
         << " sec" << endl;

    return 0;
}