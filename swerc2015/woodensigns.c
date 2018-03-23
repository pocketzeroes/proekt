#include <stdio.h>

#define MAXN   2000
#define MAXVAL 2147483647

long countInst(int iroot,int inxt,int n);
long countrowp[MAXN+1];
int p[MAXN];

int main(){
  int n, i;
  scanf("%d",&n);
  n++;
  for(i=0; i <n; i++)
    scanf("%d",&p[i]);
  for(i=0;i<n+1;i++)
    countrowp[i] = 0;
  printf("%li\n",countInst(0,1,n));
  return 0;
}
long countInst(int iroot, int inxt, int n){
  int j;
  for (j=inxt+1; j < n && (p[inxt]-p[iroot])*(p[j]-p[inxt])> 0; j++)
    inxt = j;
  if (j < n) {
    if ((p[inxt]-p[iroot])*(p[j]-p[iroot]) > 0)
      countrowp[p[iroot]+1]  = countInst(iroot,j,n);
    if (countrowp[p[inxt]+1] == 0)
      countrowp[p[inxt]+1]  = countInst(inxt,j,n);
    countrowp[p[iroot]+1] += countrowp[p[inxt]+1];
  }
  else
    countrowp[p[iroot]+1] = 1;
  return (countrowp[p[iroot]+1]) % MAXVAL;
}
