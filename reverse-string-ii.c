inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

void swap(char*nums, int i, int j) {
   char t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

char* reverseStr(char* str, int k) {
    char*s=strdup(str);
    int ssize=strlen(s);
    for (int left = 0; left < ssize; left += 2 * k) {
        for (int i = left, j = min(left + k - 1, ssize - 1); i < j; i++, j--) {
            swap(s,i,j);
        }
    }
    return s;
}
