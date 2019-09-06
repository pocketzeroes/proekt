#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>

enum{ MAXN         =     100};
enum{ MAXCIF       =     100};
enum{ MAXCIFSZ     = 1000000};
enum{ MAXCIFSZCIFS =       6};

int n;
int val[MAXN+2];
int tl[MAXN+2], tr[MAXN+2], size[MAXN+2];

int fact[MAXN+2];

int big_num[MAXCIF+2], bn_len;

void add_to_fact(int k, int add){
  int i;
  for(i=2;i*i<=k;i++){
    while(k%i==0) { fact[i]+=add; k=k/i; }
  }
  if(k>=2) fact[k]+=add;
}
void add_comb_to_fact(int k, int l){
  int i;
  if(l>k/2) l=k-l;
  for(i=k-l+1;i<=k;i++) add_to_fact(i,1);
  for(i=2;i<=l;i++) add_to_fact(i,-1);    
}
void multiply_by(int k){
  int i, tmp;
  for(i=0;i<bn_len;i++) big_num[i]*=k;
  for(i=0;i<bn_len;i++) if(big_num[i]>=MAXCIFSZ){
    tmp = big_num[i]/MAXCIFSZ;
    if(i==bn_len-1) big_num[bn_len++] = tmp;
    else big_num[i+1] += tmp;
    big_num[i] = big_num[i]%MAXCIFSZ;
  }
}
int main(){
  int i,j,tmp;
  while(1){
    scanf("%d ", &n);
    if(n==0)
      break;
    for(i=0;i<n;i++) scanf("%d ", &val[i]);
    for(i=0;i<n;i++) tl[i] = tr[i] = -1;
    for(i=1;i<n;i++)
    {
      tmp = 0;
      while(1)
      {
        if(val[i] < val[tmp]) 
        {
          if(tl[tmp] == -1) { tl[tmp] = i; break; }
          else tmp = tl[tmp];
        }
        else
        {
          if(tr[tmp] == -1) { tr[tmp] = i; break; }
          else tmp = tr[tmp];
        }
      }
    }
    for(i=n-1;i>=0;i--)
    {
      tmp = 1;  
      if(tl[i]!=-1) tmp+=size[tl[i]];
      if(tr[i]!=-1) tmp+=size[tr[i]];
      size[i] = tmp;
    }
    for(i=0;i<=MAXN;i++) fact[i]=0;
    for(i=0;i<n;i++) if(tl[i]>=0 && tr[i]>=0)
    {
      assert(size[tl[i]]>=1 && size[tr[i]]>=1);
      tmp = size[tl[i]] + size[tr[i]];
      add_comb_to_fact(tmp, size[tl[i]]);
    }
    bn_len = 1;
    big_num[0]=1;
    for(i=0;i<=MAXN;i++)
    {
      for(j=0;j<fact[i];j++) multiply_by(i);
    }
    printf("%d", big_num[bn_len-1]);
    for(i=bn_len-2; i>=0; i--) printf("%06d", big_num[i]);
    printf("\n");
  }
  return 0;
}
