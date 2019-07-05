#include<stdio.h>
#include<string.h>

enum{ MAXN = 80};

int modexp(int a,int b, int p){
  int tmp;
  if (b==0) return 1;
  if (b==1) return a;
  tmp=modexp(a,b/2,p);
  tmp=(tmp*tmp) % p;
  if (b & 1) tmp=(tmp*a) % p;
  return tmp;
}
int main(){
  char str[MAXN+1];
  int i,j,k,p,n,b[MAXN],Mx[MAXN][MAXN];
  scanf("%d",&n);
  while(n--){
    scanf("%d %s", &p, str);
    for(i=0;i<strlen(str);i++)
      b[i]=str[i]=='*'?0:str[i]-'a'+1;
    for(i=0;i<strlen(str);i++)
      for(j=0;j<strlen(str);j++)
        Mx[i][j] = modexp(i+1,j,p);
    for(i=0;i<strlen(str);i++)
      for(j=i+1;j<strlen(str);j++){
        int mult=(modexp(Mx[i][i],p-2,p)*Mx[j][i]) % p;
        for(k=i;k<strlen(str);k++)
          Mx[j][k] = (p+Mx[j][k]-((Mx[i][k]*mult) % p)) % p;
        b[j]=(p+b[j]-((b[i]*mult) % p)) % p;
      }
    for(i=strlen(str)-1;i>=0;i--){
      int sum=b[i];
      for(j=i+1;j<strlen(str);j++)
        sum=(p+sum-(Mx[i][j]*b[j] % p)) % p;
      b[i]=(sum*modexp(Mx[i][i],p-2,p)) % p;
    }
    for(i=0;i<strlen(str)-1;i++)
      printf("%d ",b[i]);
    printf("%d\n", b[strlen(str)-1]);
  }
  return 0;
}
