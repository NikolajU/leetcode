// this solution is top 0.5% fastest

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

int coinChange(int* coins, int coinsSize, int amount){
    int solutionsSize = amount+1;
    unsigned int *solutions = calloc(solutionsSize, sizeof(int));

    unsigned int smallestProblem = INT_MAX, newSolution = INT_MAX;
    unsigned int coin, currentAmount;
    unsigned char y;

    for(currentAmount = 1; currentAmount < solutionsSize; currentAmount++) {
        smallestProblem = INT_MAX;
        newSolution = INT_MAX;

        for (y = 0; y < coinsSize; y++) {
            coin = coins[y];
            if (currentAmount > coin) {
                newSolution = solutions[currentAmount-coin] +1;
            } else if (currentAmount == coin) {
                newSolution = 1;
            }

            if (newSolution < smallestProblem) {
                smallestProblem = newSolution;
            }
        }

        solutions[currentAmount] = smallestProblem;
    }

    int result = solutions[amount] == INT_MAX ? -1 : solutions[amount];
    // free(solutions);
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

    return 1;
}