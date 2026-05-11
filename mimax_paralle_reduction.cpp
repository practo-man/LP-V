#include <iostream>
#include <omp.h>
#include <cstdlib>

using namespace std;

// Function for Minimum
int minval(int arr[], int n) {
    int min_value = arr[0];

    #pragma omp parallel for reduction(min:min_value)
    for(int i = 0; i < n; i++) {
        if(arr[i] < min_value)
            min_value = arr[i];
    }

    return min_value;
}

// Function for Maximum
int maxval(int arr[], int n) {
    int max_value = arr[0];

    #pragma omp parallel for reduction(max:max_value)
    for(int i = 0; i < n; i++) {
        if(arr[i] > max_value)
            max_value = arr[i];
    }

    return max_value;
}

// Function for Sum
int sum(int arr[], int n) {
    int total = 0;

    #pragma omp parallel for reduction(+:total)
    for(int i = 0; i < n; i++) {
        total += arr[i];
    }

    return total;
}

// Function for Average
double average(int arr[], int n) {
    return (double)sum(arr, n) / n;
}

int main() {

    int n = 10;

    int arr[10] = {10, 20, 5, 40, 25, 15, 30, 35, 50, 45};

    double start, end;

    // Minimum Operation
    start = omp_get_wtime();
    int minimum = minval(arr, n);
    end = omp_get_wtime();

    cout << "Minimum Value = " << minimum << endl;
    cout << "Time for Min Operation = "
         << end - start << " seconds\n" << endl;

    // Maximum Operation
    start = omp_get_wtime();
    int maximum = maxval(arr, n);
    end = omp_get_wtime();

    cout << "Maximum Value = " << maximum << endl;
    cout << "Time for Max Operation = "
         << end - start << " seconds\n" << endl;

    // Sum Operation
    start = omp_get_wtime();
    int totalsum = sum(arr, n);
    end = omp_get_wtime();

    cout << "Sum = " << totalsum << endl;
    cout << "Time for Sum Operation = "
         << end - start << " seconds\n" << endl;

    // Average Operation
    start = omp_get_wtime();
    double avg = average(arr, n);
    end = omp_get_wtime();

    cout << "Average = " << avg << endl;
    cout << "Time for Average Operation = "
         << end - start << " seconds\n" << endl;

    return 0;
}
