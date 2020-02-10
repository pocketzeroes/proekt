#include <stdio.h>

int i,j,k,a,b;

int gcd(int a, int b) {
   if (b > a) return gcd(b,a);
   if (b == 0) return 0;  // this player loses
   if (a/b == 1) return !gcd(b,a%b); // no choice
   return 1; // this player can force a win
}

main(){
   while (2 == scanf("%d%d",&a,&b) && a) {
      if (gcd(a,b)%2) printf("Stan wins\n");
      else printf("Ollie wins\n");
   }
}
