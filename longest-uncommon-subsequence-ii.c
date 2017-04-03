int isco(char*s1, char*s2)
{
  int i,j;
  j=0;
  int s2len=strlen(s2);
  for (i=0;s1[i];i++)
  {
    while((j<s2len)&&(s2[j]!=s1[i]))
      j++;
    if (j==s2len)
      return 0;
    j++;
  }
  return 1;
}
int findLUSlength(char** strs, int strsSize)
{
  int i,j,n,cnt,ans;
  n=strsSize;
  ans=-1;
  for(i=0;i<n;i++)
  {
    cnt=0;
    for(j=0;j<n;j++)
    {
      if(isco(strs[i],strs[j])==1) 
        cnt++;
    }
    if (cnt==1){
      int slen=strlen(strs[i]);
      if(slen > ans)
        ans=slen;
    }
  }
  return ans;
}
