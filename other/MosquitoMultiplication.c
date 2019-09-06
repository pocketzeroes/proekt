#include <stdio.h>
 
enum{ MAX = 1000};

int main(){
  long f,p,l,e,r,s,n,f_pom, i;
  while( scanf(" %ld %ld %ld %ld %ld %ld %ld", &f, &p, &l, &e, &r, &s, &n)!=EOF ){
    for(i=1;i<=n;i++){
      f_pom = f;
      f=p/s;
      p=l/r;
      l=e*f_pom;
    }
    printf("%ld\n", f);
  }
  return 0;
}
