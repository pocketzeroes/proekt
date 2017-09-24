int d[100000];
int b[100000];
int lowbit(int x){
  return (x&(x-1))^x;
}
void add1(int x){
  int i;
  for (i=x;i<100000;i+=lowbit(i))
    d[i]++;
}
int get1(int x){
  int i,ret;
  ret=0;
  for (i=x;i>0;i-=lowbit(i))
    ret+=d[i];
  return ret;
}
int kEmptySlots(int*flowers, int flowersSz, int k){
  int i,j,n,x;
  n = flowersSz;
  memset(d,0,sizeof(d));
  memset(b,0,sizeof(b));
  for (i=0;i<n;i++){
    x=flowers[i];
    add1(x);
    b[x]=1;
    if ((x-k-1>=1)&&(b[x-k-1]==1)){
      if (get1(x)==get1(x-k-1)+1) 
        return i+1;
    }
    if ((x+k+1<=n)&&(b[x+k+1]==1)){
      if (get1(x)+1==get1(x+k+1)) 
        return i+1;
    }
  }
  return -1;
}
