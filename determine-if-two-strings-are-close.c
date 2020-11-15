int cmp (const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int a[26],b[26];
bool closeStrings(char*word1, char*word2){
    memset(a,0,sizeof(a));
    memset(b,0,sizeof(b));
    for(int z=0;word1[z];z++){char c=word1[z];
      a[c-'a']++;
    }
    for(int z=0;word2[z];z++){char c=word2[z];
      b[c-'a']++;
    }
    for(int i=0;i<26;i++)
      if(!!a[i]^!!b[i])
        return 0;
    qsort(a,26,sizeof(int),cmp);
    qsort(b,26,sizeof(int),cmp);
    for(int i=0;i<26;i++)
      if(a[i]!=b[i])
        return 0;
    return 1;
}
