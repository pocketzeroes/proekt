int cmpstr(const void*p1, const void*p2)
{
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}

int d[1100];

char*longestWord(char**words, int wordsSz){
  int i, j, n;
  char* ans;
  n = wordsSz;
  qsort(words, wordsSz, sizeof(char*), cmpstr);
  memset(d, 0, sizeof(d));
  ans = "";
  for(i=0; i<n; i++){
    if(strlen(words[i])==1){
      d[i] = 1;
      if(strlen(words[i]) > strlen(ans))
        ans = words[i];
      continue;
    }
    for(j=0; j<i; j++){
      if(strlen(words[j]) == strlen(words[i])-1 &&
         strncmp(words[j], words[i], strlen(words[j])) == 0 ){
        if(d[j]==1)
           d[i]= 1;
      }
    }
    if(d[i]==1){
      if(strlen(words[i]) > strlen(ans))
        ans = words[i];
    }
  }
  return ans;
}
