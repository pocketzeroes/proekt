#include <stdio.h>

int i,j,k,m,n,N;
char buf[10000];
char *b;
int val,sign,cx[2],cy[2],c[2],eq,state,coef,op;
int xnum,ynum,den;

int gcd(int a, int b){
   if (b == 0) return a;
   if (b < 0) return -gcd(a,-b);
   if (a < 0) return gcd(-a,b);
   return gcd(b,a%b);
}

void pr(int n, int d){
   if (n%d == 0) printf("%d\n",n/d);
   else printf("%d/%d\n",n/gcd(n,d),d/gcd(n,d));
}
int main(){
   scanf("%d",&N); 
   gets(buf);
   while (N--) {
      if (m++) printf("\n");
      for (i=0;i<2;i++){
         gets(buf);
         b = buf;
         op = 1;
         eq = 1;
         cx[i] = cy[i] = c[i] = 0;
         while (*b) {
            while (*b == ' ') b++;
            sign = 1;
            if (*b == '+') {
               sign = 1;
               b++;
            } else if (*b == '-') {
               sign = -1;
               b++;
            }
            if (!isdigit(*b)) val = 1;
            else val = 0;
            while (isdigit(*b)) {
               val = val * 10 + (*b-'0');
               b++;
            }
            if (*b == 'x') {
               cx[i] += sign * op * val;
               b++;
            } else if (*b == 'y') {
               cy[i] += sign * op * val;
               b++;
            } else c[i] += sign * op * val;
            while (*b == ' ') b++;
            if (*b == '=') {
               eq = -1;
               op = -1;
               b++;
            } else if (*b == '+') {
               op = eq;
               b++;
            } else if (*b == '-') {
               op = -eq;
               b++;
            } else if (!*b) break;
            else printf("oops! at %s\n",b);
         }
         //printf("%dx + %dy + %d = 0\n",cx[i],cy[i],c[i]);
      }
      den = (cx[0]*cy[1]) - (cx[1] * cy[0]);
      if (den) {
         xnum = (-c[0]*cy[1]) - (-c[1] * cy[0]);
         ynum = (cx[0]*-c[1]) - (cx[1] * -c[0]);
         pr(xnum,den);
         pr(ynum,den);
      } else if (c[0] && !cx[0] && !cy[0] || cy[1] && !cx[1] && !cy[1]) {
         printf("don't know\ndon't know\n");
      } else {
         if (cx[0] && !cy[0] && !cx[1]) pr(-c[0],cx[0]);
         else if (cx[1] && !cy[1] && !cx[0]) pr(-c[1],cx[1]);
         else if (cx[1] && !cy[1] && cx[0] && !cy[0] && cx[1]*c[0] == cx[0]*c[1]) pr(-c[0],cx[0]);
         else printf("don't know\n");
         if (cy[0] && !cx[0] && !cy[1]) pr(-c[0],cy[0]);
         else if (cy[1] && !cx[1] && !cy[0]) pr(-c[1],cy[1]);
         else if (cy[1] && !cx[1] && cy[0] && !cx[0] && cy[1]*c[0] == cy[0]*c[1]) pr(-c[0],cy[0]);
         else printf("don't know\n");
      }
      gets(buf);
   }
   return 0;
}
