// this solves the problem with less space complexity, but the trade off on speed is too big to be worth it. 

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

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

int cmpfunc (const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int coinChange(int* coins, int coinsSize, int amount){
    if (amount == 0) return 0;
    qsort(coins, coinsSize, sizeof(int), cmpfunc);
    int largestValidCoin = 0;

    for (int a = coinsSize-1; a >= 0; a--) {
        if (coins[a] <= amount) {
            largestValidCoin = coins[a];
            break;
        }
    }

    int solutionsSize = largestValidCoin;
    if (solutionsSize == 0) {
        return -1;
    }

    unsigned int *solutions = calloc(solutionsSize, sizeof(int)); // this is a circular array.

    unsigned int smallestProblem = INT_MAX, newSolution = INT_MAX;
    unsigned int coin, currentAmount, solutionsIndex, solutionsIndexWithoutCoin;
    unsigned char y;

    for(currentAmount = 1; currentAmount < amount+1; currentAmount++) {
        solutionsIndex = currentAmount % solutionsSize;
        smallestProblem = INT_MAX;
        newSolution = INT_MAX;

        for (y = 0; y < coinsSize; y++) {
            coin = coins[y];
            if (currentAmount > coin) {
                solutionsIndexWithoutCoin = (currentAmount - coin) % solutionsSize;
                newSolution = solutions[solutionsIndexWithoutCoin] + 1;
            } else if (currentAmount == coin) {
                newSolution = 1;
            }

            if (newSolution < smallestProblem) {
                smallestProblem = newSolution;
            }
        }

        solutions[solutionsIndex] = smallestProblem;
    }

    int result = solutions[solutionsIndex] == INT_MAX ? -1 : solutions[solutionsIndex];
    free(solutions);
    return result;
}

int main() {
    struct Test {
        int coinsSize;
        int amount;
        int expectedOutput;
        int *coins;
    };

    struct Test Test1;
    Test1.coinsSize = 3;
    Test1.amount = 11;
    Test1.expectedOutput = 3;

    int coinsArray1[] = {1,2,5};
    Test1.coins = &coinsArray1[0];

    int result1 = coinChange(Test1.coins, Test1.coinsSize, Test1.amount);
    printf("result1: %d %d\n", result1 == Test1.expectedOutput, result1);


    struct Test Test2;
    Test2.coinsSize = 3;
    Test2.amount = 11;
    Test2.expectedOutput = 2;

    int coinsArray2[] = {5,6,10};
    Test2.coins = &coinsArray2[0];

    int result2 = coinChange(Test2.coins, Test2.coinsSize, Test2.amount);
    printf("result2: %d %d\n", result2 == Test2.expectedOutput, result2);


    struct Test Test3;
    Test3.coinsSize = 1;
    Test3.amount = 3;
    Test3.expectedOutput = -1;

    int coinsArray3[] = {2};
    Test3.coins = &coinsArray3[0];

    int result3 = coinChange(Test3.coins, Test3.coinsSize, Test3.amount);
    printf("result3: %d %d\n", result3 == Test3.expectedOutput, result3);

    struct Test Test4;
    Test4.coinsSize = 1;
    Test4.amount = 0;
    Test4.expectedOutput = 0;

    int coinsArray4[] = {1};
    Test4.coins = &coinsArray4[0];

    int result4 = coinChange(Test4.coins, Test4.coinsSize, Test4.amount);
    printf("result4: %d %d\n", result4 == Test4.expectedOutput, result4);

    struct Test Test5;
    Test5.coinsSize = 4;
    Test5.amount = 6249;
    Test5.expectedOutput = 20;

    int coinsArray5[] = {186,419,83,408};
    Test5.coins = &coinsArray5[0];

    int result5 = coinChange(Test5.coins, Test5.coinsSize, Test5.amount);
    printf("result5: %d %d\n", result5 == Test5.expectedOutput, result5);


    struct Test Test6;
    Test6.coinsSize = 12;
    Test6.amount = 9864;
    Test6.expectedOutput = 24;

    int coinsArray6[] = {411,412,413,414,415,416,417,418,419,420,421,422};
    Test6.coins = &coinsArray6[0];

    int result6 = coinChange(Test6.coins, Test6.coinsSize, Test6.amount);
    printf("result6: %d %d\n", result6 == Test6.expectedOutput, result6);


    struct Test Test7;
    Test7.coinsSize = 2;
    Test7.amount = 2;
    Test7.expectedOutput = 2;

    int coinsArray7[] = {1,2147483647};
    Test7.coins = &coinsArray7[0];

    int result7 = coinChange(Test7.coins, Test7.coinsSize, Test7.amount);
    printf("result7: %d %d\n", result7 == Test7.expectedOutput, result7);


    struct Test Test8;
    Test8.coinsSize = 1;
    Test8.amount = 0;
    Test8.expectedOutput = 0;

    int coinsArray8[] = {1};
    Test8.coins = &coinsArray8[0];

    int result8 = coinChange(Test8.coins, Test8.coinsSize, Test8.amount);
    printf("result8: %d %d\n", result8 == Test8.expectedOutput, result8);

    return 1;
}