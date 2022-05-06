#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

void printTable(unsigned long **matrix, int len1, int len2){
    for (int i =0; i < len1; i++) {
        for (int y = 0; y < len2; y++) {
            printf("%lu ", matrix[i][y]);
        }
        printf("\n");
    }
    printf("\n");
}

#define MIN(a, b) ((a<b)?(a):(b))
#define MAX(a, b) ((a>b)?(a):(b))

int largestNumberInRangeArray(int start, int end, int* jobDifficulty) {
    int maxNumber = jobDifficulty[start];

    for (int i = start; i <= end; i++) {
        maxNumber = MAX(maxNumber, jobDifficulty[i]);
    }

    return maxNumber;
}

int forLoop(int currentCutIndex, int maxDepth, int currentDepth, int* jobDifficulty, int jobDifficultySize, unsigned long** dp) {
    int end = jobDifficultySize - (maxDepth - currentDepth) -1;
    // printf("%d %d %d %d\n", currentCutIndex, maxDepth, currentDepth, end);
    if (dp[currentCutIndex][end] != -1) {
        // printf("took from memoized %d %d %lu\n", currentCutIndex, end, dp[currentCutIndex][end]);
        // printTable(dp, jobDifficultySize, jobDifficultySize);
        return dp[currentCutIndex][end];
    }

    unsigned long minDifficulty = 4294967295;
    unsigned long newResult;

    if (currentDepth < maxDepth) {
        for (int i = currentCutIndex; i <= end ; i++) {
            newResult = largestNumberInRangeArray(currentCutIndex, i, jobDifficulty) + forLoop(i+1, maxDepth, currentDepth+1, jobDifficulty, jobDifficultySize, dp);
            // printf("%d %d %d\n", currentCutIndex, i, largestNumberInRangeArray(currentCutIndex, i, jobDifficulty));
            minDifficulty = MIN(
                minDifficulty,
                newResult
            );
        }
        newResult = minDifficulty;
    }
    else {
        newResult = largestNumberInRangeArray(currentCutIndex, end, jobDifficulty);
        // printf("%d %d %lu\n", currentCutIndex, end, newResult);
    }
    dp[currentCutIndex][end] = newResult;
    // printf("added to dp. %d %d %lu\n", currentCutIndex, end, newResult);
    // printTable(dp, jobDifficultySize, jobDifficultySize);

    return newResult;
}

int minDifficulty(int* jobDifficulty, int jobDifficultySize, int d){
    if (d > jobDifficultySize) return -1;

    unsigned long **dp = calloc(jobDifficultySize, sizeof *dp);
    for (int i=0; i < jobDifficultySize; i++) {
        dp[i] = malloc(jobDifficultySize * sizeof(unsigned long));
        memset(dp[i], -1, jobDifficultySize * sizeof(unsigned long) );
    }

    // int result = forLoop(0, d-1, 0, jobDifficulty, jobDifficultySize, dp);
    // printTable(dp, jobDifficultySize, jobDifficultySize);
    // printf("%d\n", result);
    // return result;
    return forLoop(0, d-1, 0, jobDifficulty, jobDifficultySize, dp);
}

int main() {
    int arr1[] = {6,5,4,3,2,1};
    int *arr1P = &arr1[0];

    int arr2[] = {6,5,4,2,1,7,6,5,10}; //10+6+1 = 17
    int *arr2P = &arr2[0];

    int arr3[] = {6,5,1,1,3,3}; // 6 + 1 + 3 = 10
    int *arr3P = &arr3[0];

    bool result1 = minDifficulty(arr1P, 6, 2) == 7;
    printf("result1: %d \n", result1);
    bool result2 = minDifficulty(arr2P, 9, 3) == 17;
    printf("result2: %d \n", result2);
    bool result3 = minDifficulty(arr3P, 6, 3) == 10;
    printf("result3: %d \n", result3);

    int arr4[] = {380,302,102,681,863,676,243,671,651,612,162,561,394,856,601,30,6,257,921,405,716,126,158,476,889,699,668,930,139,164,641,801,480,756,797,915,275,709,161,358,461,938,914,557,121,964,315};
    int *arr4P = &arr4[0];

    bool result4 = minDifficulty(arr4P, 47, 10) == 3807;
    printf("result4: %d \n", result4);

    int arr5[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int *arr5P = &arr5[0];

    bool result5 = minDifficulty(arr5P, 246, 10) == 0;
    printf("result5: %d \n", result4);
}