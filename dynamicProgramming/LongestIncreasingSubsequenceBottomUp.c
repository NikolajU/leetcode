#include <stdio.h>
#include <stdlib.h>


int lengthOfLIS(int* nums, int numsSize){
    if (numsSize == 0) return 0;

    int LIS = 0;
    int *dp = malloc(numsSize * sizeof(int));
    dp[0] = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if(nums[i] > dp[LIS]) { // if this number is larger than the previously found largest number, add it to dp.
            dp[LIS+1] = nums[i];
            LIS++;
        } else {
            for (int y = 0; y <= LIS; y++) {
                if(dp[y] >= nums[i]) { // overwrite dp[y] with nums[i], if nums[i] is smaller. 
                    dp[y] = nums[i];
                    break;
                }
            }
        }
    }

    // for (int i =0; i < numsSize; i++) {
    //     printf("%d ", dp[i]);
    // }

    return LIS+1;
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