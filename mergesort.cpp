/*
export OMP_NUM_THREADS=4
g++ -fopenmp mergesort.cpp
./a.out
*/
#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void generateArray(vector<int>& arr){
    for(int i=0;i<arr.size();i++){
        arr[i] = rand() % arr.size();
    }
}

vector<int> merge(vector<int>& a, vector<int>& b) {
    vector<int> res(a.size() + b.size());
    int i = 0, j = 0;
    int k = 0;
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) {
            res[k] = a[i];
            i++;
        } else {
            res[k] = b[j];
            j++;
        }
        k++;
    }
    while (i < a.size()) {
        res[k] = a[i];
        i++;
        k++;
    }
    while (j < b.size()) {
        res[k] = b[j];
        j++;
        k++;
    }
    return res;
}

vector<int> sequentialMergeSort(vector<int>& arr, int low, int high) {
    if (low == high) {
        vector<int> ba(1);
        ba[0] = arr[low];
        return ba;
    }
    int mid = (low + high) / 2;
    vector<int> fhalf = sequentialMergeSort(arr, low, mid);
    vector<int> shalf = sequentialMergeSort(arr, mid + 1, high);
    vector<int> full = merge(fhalf, shalf);
    return full;
}

vector<int> parallelMergeSort(vector<int>& arr, int low, int high) {
    if (low == high) {
        vector<int> ba(1);
        ba[0] = arr[low];
        return ba;
    }
    int mid = (low + high) / 2;
#pragma omp parallel sections
{
    #pragma omp section
    vector<int> fhalf = parallelMergeSort(arr, low, mid);
    #pragma omp section
    vector<int> shalf = parallelMergeSort(arr, mid + 1, high);
}
vector<int> full = merge(fhalf, shalf);
l
    return full;
}

int main() {
    const int size = 10000;
    vector<int> arr(size);
    generateArray(arr);
    vector<int> parallelarr = arr;

    double startTime = omp_get_wtime();
    sequentialMergeSort(arr, 0, size);
    double endTime = omp_get_wtime();
    double sequentialTime = endTime - startTime;
    cout<<"Time for Sequential Sort: "<<sequentialTime<<endl;
    startTime = omp_get_wtime();
    parallelMergeSort(arr, 0, size);
    endTime = omp_get_wtime();
    double parallelTime = endTime - startTime;
    cout<<"Time for Parallel Sort: "<<parallelTime<<endl;
    return 0;
}