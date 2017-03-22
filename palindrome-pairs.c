int checkPalindrome(char* a, char* b) {
    int lenA = strlen(a);
    int lenB = strlen(b);
    int i = 0;
    int j = lenB - 1; 
    while (i < lenA && j >= 0) {
        if (a[i] != b[j]) {
            return 1;
        }
        i += 1;
        j -= 1;
    }
    if (lenA < lenB) {
        i = 0;
        while (i < j) {
            if (b[i] != b[j]) {
                return 1;
            }
            i += 1;
            j -= 1;
        }
    } else if (lenA > lenB) {
        j = lenA - 1;
        while (i < j) {
            if (a[i] != a[j]) {
                return 1;
            }
            i += 1;
            j -= 1;
        }
    }
    return 0;
}
int** palindromePairs(char** words, int wordsSize, int** columnSizes, int* returnSize) {
    int** pairs = malloc(10000 * sizeof(int*));
    (*columnSizes) = malloc(10000 * sizeof(int));
    *returnSize = 0;
    int i, j;
    for(i = 0; i < wordsSize; i++) {
        for(j = 0; j < wordsSize; j++) {
            if(i != j && checkPalindrome(words[i], words[j]) == 0) {
                pairs[*returnSize] = malloc(2 * sizeof(int));
                pairs[*returnSize][0] = i;
                pairs[*returnSize][1] = j;
                (*columnSizes)[*returnSize] = 2;
                (*returnSize)++;
            }
        }
    }
    return pairs;
}

