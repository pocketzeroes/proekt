#include<stdio.h>
#include<string.h>

enum{ MAXS = 20};

char S[MAXS],T[MAXS];
int vis[1<<MAXS];
int tl,sl;
int fifo[2][MAXS+1][1<<MAXS];
int fstart[2][MAXS+1],fstop[2][MAXS+1];

int issubst(char *a, int al, int amsk, char*b, int bs, int bmsk){
  int i,j,dir,mx=0;
  for (j=0;j<2;j++){
    dir=1-2*j;
    for (i=0;i<al;i++){
      int same=1,k=0;
      while (same && i+dir*k>=0){
        same=(a[i+dir*k]==b[bs+k]) && (amsk&(1<<(i+dir*k))) && !(bmsk&(1<<(bs+k)));
        k+=same;
      }
      if (k>mx)
          mx=k;
    }
  }
  return mx;
}
void enq(int par, int who, int len){
  fifo[par][len][fstop[par][len]++]=who;
}
int deq(int par, int*len){
  int i;
  for (i=tl;i>=0 && fstart[par][i]>=fstop[par][i];i--);
  if (i<0)
    return -1;
  else{
    *len=i;
    return fifo[par][i][fstart[par][i]++];
  }
}
int main(){
  int n,i,l,k,m,who,next,wlen,par,ismore;
  scanf("%d",&n);
  while(n--){
    scanf("%s", &S);
    scanf("%s", &T);
    sl=strlen(S);
    tl=strlen(T);
    for (i=0;i<=tl;i++)
      fstart[0][i]=fstop[0][i]=fstart[1][i]=fstop[1][i]=0;
    for (l=0;l<(1<<tl);l++)
      vis[l]=-1;
    vis[0]=0;
    enq(0,0,0);
    ismore=1;
    par=0;
    while (ismore){
      ismore=0;
      who=deq(par,&wlen);
      while (who>-1 && who!=((1<<tl)-1)){
        int alen=0;
        for (i=0;i<tl;i++){
          int len,len2;
          len=issubst(T,tl,who,T,i,who);
          len2=issubst(S,sl,((1<<sl)-1),T,i,who);
          if (len2>len)
            len=len2;
          if (len>alen){
            next=who|((1<<(i+len))-(1<<i));
            if (vis[next]==-1){
              vis[next]=vis[who]+1;
              enq(1-par,next,wlen+len);
              ismore=1;
            }
            alen=len;
          }
          alen--;
        }
        who=deq(par,&wlen);
      }
      if (who==((1<<tl)-1))
        ismore=0;
      par=1-par;
    }
    if (vis[(1<<tl)-1]==-1)
      printf("impossible\n");
    else
      printf("%d\n",vis[(1<<tl)-1]);
  }
  return 0;
}
