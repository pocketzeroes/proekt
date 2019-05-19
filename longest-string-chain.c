int max(int a,int b){return a>b?a:b;}
int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int cmp(const void*p1, const void*p2){
  return strlen(*(char* const*) p1)<
         strlen(*(char* const*) p2)?-1:1;
}
bool is_predecessor(char*a, char*b){
    int n = strlen(a);
    if(n+1 != strlen(b))
        return false;
    for(int i = 0; i <= n; i++){
        char*bb1=strdup(b); bb1[i] = '\0';
        char*bb2=strdup(b+i+1);
        char*bb = strdup(b);
        bb[0]=0;
        strcat(bb, bb1);
        strcat(bb, bb2);
        if(strcmp(a, bb)==0)
            return true;
    }
    return false;
}
int longestStrChain(char**words, int wordsSz){
    int n = wordsSz;
    qsort(words, wordsSz, sizeof(char*), cmp);
    bool can[n][n]; memset(can, 0, sizeof(can));
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            can[i][j] = is_predecessor(words[i], words[j]);
    int dp[n]; fill(dp, n, 1);
    for (int i = 0; i < n; i++){
        for (int j = 0; j < i; j++)
            if (can[j][i])
                dp[i] = max(dp[i], dp[j] + 1);
    }
    return max_element(dp, n);
}
