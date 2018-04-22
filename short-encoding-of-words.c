int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
void swap(char*nums, int i, int j) {
   char t  = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
int minimumLengthEncoding(char**words, int wordsSz){
    int n = wordsSz;
    int ans = 0;
    for(int i = 0; i < n; i++){
        char*w = words[i];
        int len = strlen(w);
        for(int i = 0, j = len - 1; i < j; i++, j--){
            swap(w, i, j);
        }
        words[i] = w;
        ans += len + 1;
    }
    qsort(words, wordsSz, sizeof(char*), cmpstr);
    for(int i = 0; i < n; i++){
        if (i == n - 1) 
            continue;
        if(strlen(words[i]) > strlen(words[i + 1])) 
            continue;
        if(strncmp(words[i+1], words[i], strlen(words[i]))==0) {
            ans -= strlen(words[i]) + 1;
        }
    }
    return ans;
}
