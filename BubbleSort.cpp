/*
FOR RUNNING IN TERMINAL
export OMP_NUM_THREADS = 4(depends on your system)
gcc -fopenmp BubbleSort.cpp -o bsort
./bsort
*/

//delete these two cells after execution and then start code
//for colab only
!pip install git+https://github.com/adhamale2810/cuda.git
//for colab only
%load_ext nvcc_plugin

%%cu // if running in colab else not needed
#include <iostream>
#include <omp.h>

void swap(int& a, int& b){
    int temp = a;
    a = b;
    b = temp;
}

void sequentialSort(int[] arr, int size){
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void parallelSort(int[] arr, int size){
    for(int i=0;i<size-1;i++){
        for(int j=0;j<size-i-1;j++){
            #pragma omp
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void printArray(int[] arr, int size){
    for(int i=0;i<size;i++){
        std::cout<<arr[i]<<" ";
    }
}

void generateArray(int[] arr, int size){
    for(int i=0;i<size;i++){
        arr[i] = rand() % size;
    }
}

int main(){
    const int size = 10000;
    int arr[size];
    generateArray(arr,size);

    int parallelarr[size];
    std::copy(arr,arr+size,parallelarr);

    double startTime = omp_get_wtime();
    sequentialSort(arr,size);
    double endTime = omp_get_wtime();
    double sequentialTime = endTime - startTime;
    std::cout<<"Sequential Sorted Array";
    printArray(arr,size);
    std::cout<<"Time for Sequential Sort: "<<sequentialTime;

    startTime = omp_get_wtime();
    parallelSort(parallelarr,size);
    endTime = omp_get_wtime();
    double parallelTime = endTime - startTime;
    std::cout<<"Parallel Sorted Array";
    printArray(parallelarr,size);
    std::cout<<"Time for Parallel Sort: "<<parallelTime;
    return 0;
}
