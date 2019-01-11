#include <stdio.h>
enum{ MAXN = 100000};
int t[MAXN];
int a, b, c, d;

int try(int ea, int ed){
  int fail = 1;
  int i;
  int l = 0, k = 0;
  if (ea)
    t[l++] = 0;
  else { 
    while (l * (l-1) < 2*a) {
      t[l++] = 0;    
    }
  }
  if (l * (l-1) == 2*a) {
    if (ed)
      t[l+k++] = 1;
    else {  
      while (k * (k-1) < 2*d) {
        t[l+k++] = 1;
      }
    }
    if (k * (k-1) == 2*d) {
      int zo = l * k;
      if (zo > b && l) {
        int tmp = zo -b;
        int mny = tmp / l;
        if (mny <= k) {
          for (i = 0; i < mny; i++) {
            t[i] = 1;
            t[l+i] = 0;
          }
          zo -= mny * l;
        }
        if (zo > b && mny < k) {
          t[l+mny] = 0;
          t[l+mny - (zo - b)] = 1;
          zo = b;
        }
      }
      if (zo == b && (k+l)*(k+l-1)==2*(a+b+d+c)) {
        fail = 0;
        for (i = 0; i < k+l; i++) {
          printf("%1d",t[i]);
        }
        printf("\n");
      }
    }
  }
  return fail;
}
int main(){
  int i;
  int fail = 1;
  scanf("%d %d %d %d",&a, &b, &c, &d);
  if (!a) fail = try(1,0);
  if (fail && !d) fail = try(0,1);
  if (fail && !a && !d) fail = try(1,1);
  if (fail) fail = try(0,0);
  if (fail) printf("impossible\n");
  return 0;
}