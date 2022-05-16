#include <stdio.h>
#include <stdlib.h>


int lengthOfLIS(int* nums, int numsSize){
    int *dp = malloc(numsSize * sizeof(int));
    dp[numsSize-1] = 1;
    int largestFound = 1;

    for (int i = numsSize-2; i >= 0; i--) {
        dp[i] = 1;
        for (int y = i; y < numsSize; y++) {
            if (nums[i] < nums[y] && dp[i] <= dp[y] ) {
                dp[i] = dp[y]+1;
                if (largestFound < dp[y]+1) {
                    largestFound = dp[y]+1;
                    // printf("largest found breaking\n");
                    break;
                }
            }
            // printf("%d %d\n", i, y);
        }
    }

    for (int i =0; i < numsSize; i++) {
        // printf("%d ", dp[i]);
    }

    return largestFound;
}

int main() { // if its bigger and the same.
    int nums1[] = {10,9,2,5,3,7,101,18};
    int result1 = lengthOfLIS(nums1, 8);
    printf("result1: %d\n", result1 == 4);

    int nums2[] = {0,1,0,3,2,3};
    int result2 = lengthOfLIS(nums2, 6);
    printf("result2: %d\n", result2 == 4);

    int nums3[] = {7,7,7,7,7,7,7};
    int result3 = lengthOfLIS(nums3, 7);
    printf("result3: %d\n", result3 == 1);


}