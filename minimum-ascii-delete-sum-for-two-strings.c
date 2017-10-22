char*s1;
char*s2;
int d[1100][1100];

int doit(int x,int y){
  int ans, tmp;
  if ((x==0)&&(y==0))
    return 0;
  if (d[x][y]!=-1)
    return d[x][y];
  ans=2000000000;
  if (x>0){
    tmp=doit(x-1, y);
    if (tmp+s1[x-1]<ans)
      ans=tmp+s1[x-1];
  }
  if (y>0){
    tmp=doit(x, y-1);
    if (tmp+s2[y-1]<ans)
      ans=tmp+s2[y-1];
  }
  if ((x>0)&&(y>0)&&(s1[x-1]==s2[y-1])){
    tmp=doit(x-1, y-1);
    if (tmp<ans)
      ans=tmp;
  }
  d[x][y]=ans;
  return ans;
}
int minimumDeleteSum(char*ss1, char*ss2){
  s1 = ss1;
  s2 = ss2;
  memset(d,-1,sizeof(d));
  return doit(strlen(s1), strlen(s2));
}
