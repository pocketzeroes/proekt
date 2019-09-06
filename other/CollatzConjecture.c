#include <stdio.h>
typedef long long ll;
enum{SIZE      = 1000000};
enum{MAX_COUNT = 1000};

ll values_a[MAX_COUNT];
ll values_b[MAX_COUNT];

ll*prepare(ll*ptr, ll value){
  while (1){
    *ptr = value;
    if (value == 1)
      return ptr;
    ++ptr;
    value = (value % 2) ? (3 * value + 1) : (value / 2);
  }
}
int main(){
  int a, b;
  ll * ptr_a, * ptr_b;
  while (1){
    scanf("%d %d", &a, &b);
    if ((a == 0) && (b == 0))
      break;
    ptr_a = prepare(values_a, a);
    ptr_b = prepare(values_b, b);
    while ((ptr_a >= values_a) && (ptr_b >= values_b) && (*ptr_a == *ptr_b)){
      --ptr_a;
      --ptr_b;
    }
    ++ptr_a;
    ++ptr_b;
    printf("%d needs %d steps, %d needs %d steps, they meet at %lld\n", a, (ptr_a - values_a), b, (ptr_b - values_b), *ptr_a);
  }
  return 0;
}
