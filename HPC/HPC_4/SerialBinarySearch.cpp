#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int size = 4096;
int key = 100;


int serialBinarySearch(int* arr, int key, int left, int right) {
    int mid;
    while(right >= left) {
        mid = (left + right) >> 1;
        
        if(arr[mid] == key)
            return mid;

        if(arr[mid] < key)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}

int main(int argc, char** argv) {
    int* array;
    int arrayMemory = size * sizeof(int);
    array = (int*) malloc(arrayMemory);

    for(int i=0; i<size; i+=1)
        array[i] = i + 1;

    double start, end;

    start = clock();
    int index = serialBinarySearch(array, key, 0, size);
    end = clock();

    if(index != -1)
        printf("Element %d found at position %d\n", key, index);
    else
        printf("Element %d not found\n", key);

    printf("Time required for searching: : %lf ms\n", end - start);

    return 0;
}
