#define MIN(a,b) (((a)<(b))?(a):(b))

int minDistance(char*word1,char*word2) {
    int m = strlen(word1);
    int n = strlen(word2);
    if(m < n)
        return minDistance(word2, word1);
    int f[n + 1];
    memset(f, 0, sizeof(f));
    size_t upper_left;
    for(size_t i = 0; i < n + 1; ++i)
        f[i] = i;
    for(size_t i = 1; i < m + 1; ++i) {
        upper_left = f[0];
        f[0] = i;
        for(size_t j = 1; j < n + 1; ++j) {
            size_t upper = f[j];
            if(word1[i - 1] == word2[j - 1])
                f[j] = upper_left;
            else {
                f[j] = 1 + MIN(upper_left, MIN(f[j - 1], f[j]));
            }
            upper_left = upper;
        }
    }
    return f[n];
}

