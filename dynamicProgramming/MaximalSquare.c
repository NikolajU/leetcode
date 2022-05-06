#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "uthash.h"

void printTable(int **matrix, int len1, int len2){
    for (int i =0; i < len1; i++) {
        for (int y = 0; y < len2; y++) {
            printf("%d ", matrix[i][y]);
        }
        printf("\n");
    }
    printf("\n");
}

#define MIN(a, b) ((a<b)?(a):(b))
#define MAX(a, b) ((a>b)?(a):(b))

int maximalSquare(char** matrix, int matrixSize, int* MatrixColumnsSize){
    // int **dp;
    short i, y, largestSquareFound = 0;

    // dp = calloc(matrixSize+1, sizeof *dp);
    // for (i=0; i < matrixSize + 1; i++) {
    //     dp[i] = calloc(*MatrixColumnsSize+1, sizeof *(dp[i]));
    // }

    register short *dp1 = (short *)calloc(*MatrixColumnsSize+1, sizeof(short));
    register short *dp2 = (short *)calloc(*MatrixColumnsSize+1, sizeof(short));
    register short *temp;

    // printTable(dp, matrixSize, *MatrixColumnsSize);

    for (i = matrixSize-1; i >= 0 ; --i) {
        for (int y = *MatrixColumnsSize-1; y >= 0; --y) {
            if (matrix[i][y] == '0') {
                dp1[y] = 0;
            }
            else {
                dp1[y] = 1;
                if (largestSquareFound == 0) largestSquareFound=1;
                bool isSquare = dp2[y] > 0 && dp2[y+1] > 0 && dp1[y+1] > 0;
                if (isSquare) {
                    int smallesSquare = MIN(MIN(dp2[y],dp2[y+1]), dp1[y+1]);
                    dp1[y] += smallesSquare;
                    if (dp1[y] > largestSquareFound) largestSquareFound = dp1[y];
                }
            }
        }

        // swap
        temp = dp1;
        dp1 = dp2;
        dp2 = temp;
    }

    return largestSquareFound*largestSquareFound;
};

int main(){
    char **matrix1;
    matrix1 = malloc(4 * sizeof *matrix1);
    // char matrix2[] = {'1', '0', '1', '0', '0'};
    matrix1[0] = "10100";
    matrix1[1] = "10111";
    matrix1[2] = "11111";
    matrix1[3] = "10010";

    int a = 5;
    int *MatrixColumnsSize = &a;

    char **matrix2;
    matrix2 = malloc(sizeof *matrix2);
    matrix2[0] = "101";

    int b = 5;
    int *bPointer = &b;

    bool result1 = maximalSquare(matrix1, 4, MatrixColumnsSize) == 4;
    printf("result1: %d \n", result1);

    bool result2 = maximalSquare(matrix2, 1, bPointer) == 1;
    printf("result2: %d \n", result2);

}