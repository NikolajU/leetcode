#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX(a,b) ( a>b ? a: b )

// dp func should take all states, and return result (profit)
int dpfunc(int tradesRemaining, int i, bool holding, int*** dp, int* prices, int pricesSize) {
    // printf("%d, %d\n", i, holding);

    if (tradesRemaining == 0 || i >= pricesSize) {
        // printf("no trades or i\n");
        return 0;
    }

    // if memoized.
    if (dp[holding][tradesRemaining][i] != -1) {
        // printf("took from memoized\n");
        return dp[holding][tradesRemaining][i];
    }

    int profit;
    if (!holding) { // if not holding, you can buy or do nothing.
        profit = MAX(
            -prices[i] + dpfunc(tradesRemaining, i+1, true, dp, prices, pricesSize), // buy
            dpfunc(tradesRemaining, i+1, holding, dp, prices, pricesSize) // hold
        );
    }
    else if (holding) { // if holding, you can sell or do nothing.
        profit = MAX(
            prices[i] + dpfunc(tradesRemaining-1, i+1, false, dp, prices, pricesSize), // sell
            dpfunc(tradesRemaining, i+1, holding, dp, prices, pricesSize) // hold
        );
    }

    dp[holding][tradesRemaining][i] = profit;
    return profit;
}

int maxProfit(int k, int* prices, int pricesSize) {
    int ***dp = malloc(2 * sizeof(**dp)); // holding or not holding
    for (int i = 0; i < 2; i++) { // holding or not holding
        dp[i] = malloc((k+1) * sizeof(*dp)); // tradesRemaining
        for (int y = 0; y < (k+1); y++) { // tradesRemaining
            dp[i][y] = malloc(pricesSize * sizeof(int)); // i
            memset(dp[i][y], -1, pricesSize * sizeof(int)); // i
        }
    }

    return dpfunc(k, 0, false, dp, prices, pricesSize);
}

int main() {
    int prices1[] = {3,2,6,5,0,3};
    int result1 = maxProfit(2, &prices1[0], 6);
    printf("result1: %d %d\n", result1 == 7, result1);

    int prices2[] = {2,4,1};
    int result2 = maxProfit(2, &prices2[0], 3);
    printf("result2: %d %d\n", result2 == 2, result2);

}