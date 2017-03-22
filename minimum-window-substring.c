char *minWindow(char*S, char*T){
  int tlen = strlen(T);
  int slen = strlen(S);
  if(slen < tlen)         return "";
  if(S==NULL || T==NULL)  return "";
  int i=0;
  int count = 0;
  char * re;
  int *need2Find = (int *) malloc(sizeof(int)*256);memset(need2Find,0,sizeof(int)*256);
  int *hasFound  = (int *) malloc(sizeof(int)*256);memset(hasFound ,0,sizeof(int)*256);
  int p = 0;
  int start=0,end=0,minStart = 0,minEnd = -1;
  while(p<tlen){
    need2Find[T[p]]++;
    p++;
  }
  while(end<slen){
    if(need2Find[S[end]]>0){
      hasFound[S[end]]++;
      if(hasFound[S[end]]<=need2Find[S[end]])
        count++;
    }
    if(count == tlen){
      if(minEnd < 0)
        minEnd = slen-1;
      while(start<=end){
        if(need2Find[S[start]]>0){
          if(hasFound[S[start]]>need2Find[S[start]])
            hasFound[S[start]]--;
          else
            break;
        }
        start++;
      }
      if((end-start)<(minEnd-minStart))
      {
        minEnd = end;
        minStart = start;
      }
    }
    end++;
  }
  re = (char*)malloc( (minEnd-minStart+2) );
  memset(re,0,(minEnd-minStart+2));
  i  = 0;
  while(minStart<=minEnd){
    *(re+i) = S[minStart];
    minStart++;
    i++;
  }
  return re ;
}


