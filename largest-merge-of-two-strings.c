#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

char*largestMerge(char*s, char*t){
    int n = strlen(s),
        m = strlen(t);
    char ret[n+m+1]; clr(ret);
    int i = 0, j = 0, p = 0;
    for(;i < n  && j < m;){
        int k, l;
        for(k = i, l = j; k < n && l < m && s[k] == t[l]; k++,l++);
        if(k >= n){
            ret[p++] = t[j++];
        }
        else if(l >= m){
            ret[p++] = s[i++];
        }
        else if(s[k] > t[l]){
            ret[p++] = s[i++];
        }
        else{
            ret[p++] = t[j++];
        }
    }
    while(i < n)
      ret[p++] = s[i++];
    while(j < m)
      ret[p++] = t[j++];
    return strdup(ret);
}
