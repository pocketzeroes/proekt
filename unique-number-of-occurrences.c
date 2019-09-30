int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
bool uniqueOccurrences(int*arr, int arrSz){
    int s[2005]; memset(s,0,sizeof(s));
    for(int z=0;z<arrSz;z++){int i=arr[z];
      s[i+1000]++;
    }
    qsort(s, 2005, sizeof(int), cmp);
    for(int i=0;i<2004;i++)
        if(s[i]&&s[i+1]==s[i])
            return 0;
    return 1;
}
