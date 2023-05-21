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

int maxValue(int arr[],int size){
    int max_val = INT_MIN;
    #pragma omp parallel for reduction(max:max_val)
    for(int i=0;i<size;i++){
        if(arr[i]>max_val){
            max_val = arr[i];
        }
    }
    return max_val;
}

int main(){
    const int size = 10000;
    int arr[size];
    generateArray(arr,size);
    printArray(arr,size);
    cout<<"Maximum Value: "<<maxValue(arr,size)<<endl;
}
