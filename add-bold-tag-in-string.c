int d  [2000];
int kmp[2000];
char*concat(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s",a,b);
  return ptr;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char* addBoldTag(char* s, char**a, int aSz){
  int i,j,k,t,now;
  char*ret=strdup("");
  memset(d,0,sizeof(d));
  for (t=0; t<aSz; t++){
    kmp[0]=0;
    kmp[1]=0;
    j=0;
    int atlen = strlen(a[t]);
    for (i=2; i <= atlen; i++){
      while((j>0) && (a[t][i-1] != a[t][j]))
        j=kmp[j];
      if (a[t][i-1] == a[t][j])
        j++;
      kmp[i] = j;
    }
    now=0;
    for (j=0; s[j]; j++){
      while((now>0) && (a[t][now]!=s[j]))
        now=kmp[now];
      if (a[t][now]==s[j])
        now++;
      if (now == atlen){
        d[j+1-atlen]++;
        d[j+1]--;
      }
    }
  }
  now=0;
  if(ret)free(ret); ret = strdup("");
  for (i=0; s[i]; i++){
    if ((now==0) && (d[i]>0))
      ret=concat(ret, "<b>");
    if ((now>0) && (now+d[i]<=0))
      ret=concat(ret, "</b>");
    now+=d[i];
    ret = concatc(ret, s[i]);
  }
  if (now>0)
    ret=concat(ret, "</b>");
  return ret;
}




























