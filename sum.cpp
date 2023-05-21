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

int sumArray(int arr[], int size){
    int sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for(int i=0;i<size;i++){
        sum+=arr[i];
    }
    return sum;
}

int main(){
    const int size = 10000;
    int arr[size];
    generateArray(arr,size);
    printArray(arr,size);
    cout<<"Sum: "<<sumArray(arr,size)<<endl;
}