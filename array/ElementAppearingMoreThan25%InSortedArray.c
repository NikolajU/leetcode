#include <stdio.h>

int findSpecialInteger(int* arr, int arrSize){
    int startIndex = 0, currentNumber = arr[0];
    double divided =  arrSize/4;
    printf("divided: %f\n", divided);

    for(int i=1; i < arrSize; i++) {
        int newNumber = arr[i];
        printf("newNumber: %d\n", newNumber);
        if (newNumber != currentNumber || i == arrSize-1) {
            printf("difference: %d, currentNumber: %d largerThan: %d\n", i-startIndex, currentNumber, i-startIndex > divided);
            if (i-startIndex > divided) return currentNumber;
            
            startIndex = i;
            currentNumber = newNumber;
        }
    }

    return -1;
}

int main() {
    int arr1[] = {1,2,2,6,6,6,6,7,10};
    int arr2[] = {1,1};
    int arr3[] = {0,1,1,1};
    int arr4[] = {1,2,3,3};
    int *arr1P = &arr1[0];
    int *arr3P = &arr3[0];
    int *arr4P = &arr4[0];

    // int result1 = findSpecialInteger(arr1P, 9);
    // int result3 = findSpecialInteger(arr3P, 4);
    int result4 = findSpecialInteger(arr4P, 4);

    // printf("%d\n", result1);
    // printf("%d\n", result3);
    printf("%d\n", result4);


}
