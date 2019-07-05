#include <stdio.h>

enum{ MAXN = 50};

int x[MAXN],y[MAXN];

int main(){
  int n,s,h,i,j,k,found;
  scanf("%d",&n);
  while(n--){
    scanf("%d %d", &s, &h);
    for(i=0; i<h; i++)
      scanf("%d %d", &x[i], &y[i]);
    found=0;
    for(i=0;i<s && !found;i++){
      for(j=0;j<s && !found;j++){
        found=1;
        for(k=0;k<h && found;k++){
          int leash = (i-x[k])*(i-x[k])+(j-y[k])*(j-y[k]);
          found = leash && leash<=i*i && leash<=(s-i)*(s-i) && leash<=j*j && leash<=(s-j)*(s-j);
        }
      }
    }
    if(found)
      printf("%d %d\n", i-1, j-1);
    else
      printf("poodle\n");
  }
  return 0;
}
