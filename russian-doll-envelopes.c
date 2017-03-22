
void sort(int** nums, int start, int end) {
    if (start >= end) return;
    int i = start-1, j;
    for (j = start ; j < end ; j++) {
        if (nums[j][0] <= nums[end][0]) {
            i++;
            int* t = nums[i];
            nums[i] = nums[j];
            nums[j] = t;
        }
    }
    i++;
    int* t = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
    sort(nums, start, i-1);
    sort(nums, i+1, end);
}
int maxEnvelopes(int** envelopes, int envelopesRowSize, int envelopesColSize) {
    int* dolls = malloc(envelopesRowSize * sizeof(int));
    int i, j, maxDolls = 0;
    for(i = 0; i < envelopesRowSize; i++) {
        dolls[i] = 1;
    }
    sort(envelopes, 0, envelopesRowSize - 1);
    for(i = 0; i < envelopesRowSize; i++) {
        for(j = i - 1; j >= 0; j--) {
            if((envelopes[j][0] < envelopes[i][0]) && (envelopes[j][1] < envelopes[i][1]) && (dolls[j] + 1 > dolls[i])) {
                dolls[i] = dolls[j] + 1;
            }
        }
        if(dolls[i] > maxDolls) {
            maxDolls = dolls[i];
        }
    }
    return maxDolls;
}


