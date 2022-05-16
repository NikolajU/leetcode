#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void wordBreak2(char * s, char ** wordDict, int wordDictSize, bool* dp, int fromIndex){
    int slength = strlen(s);
    if ((fromIndex > 0 && dp[fromIndex-1]) == 1 || dp[slength-1] == 1) {
        // printf("took from memoized fromIndex: %d\n", fromIndex);
        return;
    }

    char subString[slength+1];
    strcpy(subString, s+fromIndex); // substring is smaller than 

    for (int i = strlen(subString); i > 0; i--) { // iterate backwards through string s.
        subString[i] = '\0'; // make substring smaller by one char.

        for (int y=0; y < wordDictSize; y++) { // iterate through wordDict.
            // printf("%s %s fromIndex: %d\n", wordDict[y], subString, fromIndex);
            if (strcmp(wordDict[y], subString) == 0) { // if the dict word == subString.
                // printf("match %d %d\n", i+fromIndex, slength);

                if (i+fromIndex == slength) { // if the solution has been found.
                    // printf("solution found\n");
                    dp[slength-1] = 1;
                    return;
                }

                wordBreak2(s, wordDict, wordDictSize, dp, i+fromIndex);
                dp[i+fromIndex-1] = 1;
                break;
            }
        }
    }
}


bool wordBreak(char * s, char ** wordDict, int wordDictSize){
    int slength = strlen(s);
    bool *dp = calloc(slength, sizeof(bool)); // change to 1, if this index works. change to -1, if the index has been visited and it doesn't work.
    wordBreak2(s, wordDict, wordDictSize, dp, 0);
    // for(int i =0; i < slength; i++) {
    //     printf("%d ", dp[i]);
    // }
    // printf("\n");
    // for(int i =0; i < slength; i++) {
    //     printf("%c ", s[i]);
    // }
    // printf("\n");


    return dp[slength-1];
}

int main() {
    char *wordDict1[2];
    wordDict1[0] = "leet";
    wordDict1[1] = "code";

    bool result1 = wordBreak("leetcode", wordDict1, 2);
    printf("%d\n", result1);


    char *wordDict2[2];
    wordDict2[0] = "apple";
    wordDict2[1] = "pen";

    bool result2 = wordBreak("applepenapple", wordDict2, 2);
    printf("%d\n", result2);

    char *wordDict3[5];
    wordDict3[0] = "cats";
    wordDict3[1] = "dog";
    wordDict3[2] = "sand";
    wordDict3[3] = "and";
    wordDict3[4] = "cat";

    bool result3 = wordBreak("catsandog", wordDict3, 5);
    printf("%d\n", result3 == false);


    bool result4 = wordBreak("catsanddog", wordDict3, 5);
    printf("%d\n", result4 == true);


    char *wordDict5[4];
    wordDict5[0] = "catsand";
    wordDict5[1] = "dog";
    wordDict5[2] = "sand";
    wordDict5[3] = "cat";

    bool result5 = wordBreak("catsanddog", wordDict5, 4);
    printf("%d\n", result5 == true);


    char *wordDict6[4];
    wordDict6[0] = "a";
    wordDict6[1] = "abc";
    wordDict6[2] = "b";
    wordDict6[3] = "cd";

    bool result6 = wordBreak("abcd", wordDict6, 4);
    printf("%d\n", result6 == true);

}
