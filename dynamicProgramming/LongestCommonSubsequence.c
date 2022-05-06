#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX(a, b) ((a>b)?(a):(b))

void printTable(int **matrix, int len1, int len2){
    for (int i =0; i < len1; i++) {
        for (int y = 0; y < len2; y++) {
            printf("%d ", matrix[i][y]);
        }
        printf("\n");
    }
    printf("\n");
}

int find_lcs(int **dp, int len1, int len2, char *t1, char *t2, int y, int x){
    if (y >= len1 || x >= len2) return 0;

    // Do we already know the result?
    int result = dp[y][x];

    // Yes. Return it
    if(result>=0) return result;

    // Insert some clever code to compute the result
    char char1 = t1[y];
    char char2 = t2[x];
    // printf("char %d: %c char %d: %c\n", y, char1, x, char2);

    result = char1 == char2 ? 1 : 0;
    if (char1 == char2) {
        result = 1 + find_lcs(dp, len1, len2, t1, t2, y+1, x+1);
    }
    else {
        result = MAX(
            find_lcs(dp, len1, len2, t1, t2, y+1, x),
            find_lcs(dp, len1, len2, t1, t2, y, x+1)
        );
    }

    // Memoize the result so we have it next time we need it
    dp[y][x] = result;
    // printTable(dp, len1, len2);

    // Return the result
    return result;
}

int longestCommonSubsequence(char * text1, char * text2){
    int len1 = strlen(text1);
    int len2 = strlen(text2);

    int **dp; // dp is a pointer that points to dp[0]. dp[0...n] are pointers that point to dp[0...n][0] which is an integer.
    dp = calloc(len1, sizeof *dp);
    for (int i=0; i<len1; i++){
        dp[i] = calloc(len2, sizeof *(dp[i]));
    }
    for (int i = 0; i < len1; i++)
    for (int y = 0; y < len2; y++) {
        dp[i][y] = -1;
    }

    // int *dp1 = (int *)calloc(len1, sizeof(int));
    // int *dp2 = (int *)calloc(len2, sizeof(int));

    find_lcs(dp, len1, len2, text1, text2, 0, 0);
    // printTable(dp, len1, len2);

    return dp[0][0];
}

int main(){
    char text1[] = "abcde";
    char text2[] = "ace";
    char text3[] = "hdlkjsafjrkoewhlrewqhjlknmfds";
    char text4[] = "jhlkrehtjkdnmdsfhjlrewqrndsfman";

    char text5[] = "bsbininm";
    char text6[] = "jmjkbkjkv";

    char text7[] = "abcba";
    char text8[] = "abcbcba";

    bool result1 = longestCommonSubsequence(text1, text2) == 3;
    bool result2 = longestCommonSubsequence(text3, text4) == 15;
    bool result3 = longestCommonSubsequence(text5, text6) == 1;
    bool result4 = longestCommonSubsequence(text7, text8) == 5;

    printf("result1: %d \n", result1);
    printf("result2: %d \n", result2);
    printf("result3: %d \n", result3);
    printf("result4: %d \n", result4);

}