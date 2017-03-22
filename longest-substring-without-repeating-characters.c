#define MAX(a,b) (((a)>(b))?(a):(b))

int lengthOfLongestSubstring(char* s) {
    int n = strlen(s), ans = 0;
    int*index = malloc(sizeof(int)*128);
    memset(index,0,sizeof(int)*128);
    for (int j = 0, i = 0; j < n; j++) {
        i =   MAX(index[s[j]], i);
        ans = MAX(ans, j - i + 1);
        index[s[j]] = j + 1;
    }
    return ans;
}
