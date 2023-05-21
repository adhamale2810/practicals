%%cu
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

double averageArray(int arr[], int size){
    int sum = 0;
    int count = 0;
    #pragma omp parallel for reduction(+:sum) reduction(+:count)
    for(int i=0;i<size;i++){
        sum+=arr[i];
        count++;
    }
    return sum/count;
}

int main(){
    const int size = 10000;
    int arr[size];
    generateArray(arr,size);
    printArray(arr,size);
    cout<<"Average: "<<averageArray(arr,size)<<endl;
}
