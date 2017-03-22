inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int characterReplacement(char* s, int k) {
    int cache[26]={0};
    int i = 0, j = 0, times = k, res = 0;
    for (; s[j] ; ++j) {
        ++cache[s[j] - 'A'];
        if (s[j] != s[i]) {
            --times;
            if (times < 0) {
                res = max(res, j - i);
                while (i < j && times < 0) {
                    --cache[s[i++] - 'A'];
                    times = k - (j - i + 1 - cache[s[i] - 'A']);
                }
            }
        }
    }
    return max(res, j - i + min(i, times));
}
