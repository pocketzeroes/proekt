int a[105],t[26],d[4];
char ans[256];

char*longestNiceSubstring(char*s){
  int n=strlen(s),i,j;
  memset(a,0,sizeof(a));
  for(i=0;i<n;i++){
    memset(t,0,sizeof(t));
    memset(d,0,sizeof(d));
    d[0]=26;
    for(j=i;j<n;j++){
      if(s[j]>='a'){
        d[t[s[j]-'a']]--;
        t[s[j]-'a']|=1;
        d[t[s[j]-'a']]++;
      }
      else{
        d[t[s[j]-'A']]--;
        t[s[j]-'A']|=2;
        d[t[s[j]-'A']]++;
      }
      if(d[0]+d[3]==26)
        a[i]=j-i+1;
    }
  }
  for(i=j=0;i<n;i++)
    if(a[i]>a[j])
      j=i;
  int asz=0;
  for(i=j;i<j+a[j];i++)
    ans[asz++]=s[i];
  ans[asz]='\0';
  return strdup(ans);
}
