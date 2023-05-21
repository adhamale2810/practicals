/*
export OMP_NUM_THREADS=4
g++ -fopenmp bubblesort.cpp
./a.out
*/
#include <iostream>
#include <omp.h>
using namespace std;

void generateArray(int arr[], int size){
    for(int i=0;i<size;i++){
        arr[i] = rand() % size;
    }
}

void printArray(int arr[], int size){
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

int minArray(int arr[], int size){
    int min_val = INT_MAX;
    #pragma omp parallel for reduction(min:min_val)
    for(int i=0;i<size;i++){
        if(arr[i]<min_val){
            min_val = arr[i];
        }
    }
    return min_val;
}

int main(){
    const int size = 10000;
    int arr[size];
    generateArray(arr,size);
    printArray(arr,size);
    cout<<"Minimum: "<<minArray(arr,size)<<endl;
}