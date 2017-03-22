inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int longestSubstringHelper(char*s, int k, int start, int end){
    int count[26];
    memset(count,0,sizeof(count));
    for (int i = start; i < end; ++i) 
        ++count[s[i] - 'a'];
    int max_len = 0;
    for (int i = start; i < end;) {
        while (i < end && count[s[i] - 'a'] < k) 
            ++i;
        if (i == end) 
            break;
        int j = i;
        while (j < end && count[s[j] - 'a'] >= k) 
            ++j;
        if (i == start && j == end) 
            return end - start; 
        max_len = max(max_len, longestSubstringHelper(s, k, i, j));
        i = j;
    }
    return max_len;
}
int longestSubstring(char*s, int k) {
    return longestSubstringHelper(s, k, 0, strlen(s) );
}
