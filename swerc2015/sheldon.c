#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <stdlib.h>


int max(int x, int y){  return x <= y ? y : x;}
int min(int x, int y){  return x <= y ? x : y;}

int int_get(void){
  int result;
  scanf("%d", &result);
  return result;
}
void ints_println_basic(const int *a, int n){
  if (n > 0){
    printf("%d", a[0]);
    for (int i = 1; i < n; i++)
      printf(" %d", a[i]);
  }
  printf("\n");
}
int bits(long long x, int *a){
  int result = 0;
  if (x == 0)
    a[result++] = 0;
  else
    while (x > 0){
      a[result++] = x & 1;
      x >>= 1;
    }
  return result;
}
char *bit_string(long long x, char *s){
  int a[64];
  char *p = s;
  int n = bits(x, a);
  for (int i = n-1; i >= 0; i--)
    *p++ = '0' + a[i];
  *p = '\0';
  return s;
}
void ll_println_basic(const long long *a, int n){
  if (n > 0){
    printf("%lld", a[0]);
    for (int i = 1; i < n; i++)
      printf(" %lld", a[i]);
  }
  printf("\n");
}
void ll_print_bits(const long long *a, int n){
  char s[65];
  for (int i = 0; i < n; i++)
    printf("%s %lld\n", bit_string(a[i], s), a[i]);
}
void test_bits(void){
  long long x;
  while (scanf("%lld", &x) != EOF){
    int a[65];
    int n = bits(x, a);
    ints_println_basic(a, n);
    char s[65];
    printf("%s\n", bit_string(x, s));
  }
}
int ll_sign(long long x){
  int result = 0;
  if (x > 0)
    result = 1;
  else if (x < 0)
    result = -1;
  return result;
}
long long ll_cmp(long long x, long long y){
  return x - y;
}
int ll_cmp_v1(const void *p, const void *q){
  return ll_sign(*(long long *) p - *(long long *) q);
}
void lls_qsort(long long *a, int n){
  qsort((void*)a, n, sizeof(long long), ll_cmp_v1);
}
int lls_is_sorted(long long *a, int n){
  for (int i = 1; i < n; i++)
    if (a[i-1] >= a[i])
      return 0;
  return 1;
}
int lls_unique(long long *a, int n){
  int result = 0;
  int i = 0;
  while (i < n){
    long long k = a[i];
    a[result++] = a[i];
    do
      i++;
    while (i < n && a[i] == k);
  }
  return result;
}
int first_run(const int *a, int n){
  assert(n > 0);
  int result = 0;
  int k = a[result++];
  while (result < n && a[result] == k)
    result++;
  return result;
}
int ints_runs(const int *a, int n, int *b){
  int result = 0;
  int i = 0;
  while (i < n){
    int r = first_run(a+i, n-i);
    b[result++] = r;
    i += r;
  }
  return result;
}
int equals_every_other(const int *a, int n){
  for (int i = 2; i < n; i+=2)
    if (a[0] != a[i])
      return 0;
  return 1;
}
int is_sheldon_array(const int *a, int n){
  return equals_every_other(a, n) && equals_every_other(a+1, n-1);
}
int is_sheldon(long long x){
  int a[64];
  int n = bits(x, a);
  int b[64];
  int m = ints_runs(a, n, b);
  int result = is_sheldon_array(b, m);
  return result;
}
int lls_count_between(const long long *a, int n, long long x, long long y){
  int result = 0;
  for (int i = 0; i < n; i++)
    if (x <= a[i] && a[i] <= y)
      result++;
  return result;
}
long long ones(int x){
  assert(x <= 63);
  return LLONG_MAX >> (63 - x);
}
long long ones_zeros(int x, int y){
  assert(x+y <= 63);
  return ones(x) << y;
}
void unit_test_ones(void){
  assert(ones(0) == 0);
  assert(ones(63) == LLONG_MAX);
  assert(ones(10) == 1023);
  assert(ones(1) == 1);
}
void unit_test_ones_zeros(void){
  assert(ones_zeros(0, 0) == 0);
  assert(ones_zeros(4, 1) == 30);
  assert(ones_zeros(10, 4) == 1023 * 16);
  assert(ones_zeros(1, 10) == 1024);
}
int sheldon(int maxbits, int x, int y, long long *a){
  assert(maxbits <= 63);
  assert(x >= 1);
  assert(y >= 1);
  assert(x <= maxbits);
  int result = 0;
  long long z1 = ones(x);
  long long z = z1;
  a[result++] = z;
  int s = x;
  if (s < maxbits)
    while (s + y <= maxbits){
      z <<= y;
      a[result++] = z;
      s += y;
      if (s + x <= maxbits){
        z = (z << x) | z1;
        a[result++] = z;
      }
      s += x;
    }
  return result;
}
void test_sheldon(void){
  int maxbits;
  int x;
  int y;
  while (scanf("%d%d%d", &maxbits, &x, &y) != EOF){
    long long a[100000];
    int n = sheldon(maxbits, x, y, a);
    ll_print_bits(a, n);
  }
}
int sheldon_all(int x, long long *a){
  int result = 0;
  for (int i = 1; i <= x; i++)
    for (int j = 1; j <= x - i + 1; j++)
      result += sheldon(x, i, j, a+result);
  return result;
}
int sheldon_all_detailed(int x, long long *a){
  int result = 0;
  for (int i = 1; i <= x; i++)
    for (int j = 1; j <= x - i + 1; j++){
      int r0 = result;
      result += sheldon(x, i, j, a+result);
      printf("%d %d\n", i, j);
      ll_print_bits(a + r0, result - r0);
      printf("----\n");
    }
  return result;
}
void test_sheldon_all_detailed(void){
  int x = int_get();
  long long a[100000];
  int n = sheldon_all_detailed(x, a);
  lls_qsort(a, n);
  printf("%d\n", n);
  ll_println_basic(a, n);
  printf("----\n");
  printf("%d\n", n);
}
void test_sheldon_all(void){
  int x = int_get();
  long long a[100000];
  int n = sheldon_all(x, a);
  lls_qsort(a, n);
  printf("%d\n", n);
  n = lls_unique(a, n);
  printf("%d\n", n);
  ll_println_basic(a, n);
}
int count_sheldon(int x, int y){
  int result = 0;
  for (int i = x; i <= y; i++)
    if (is_sheldon(i))
      result++;
  return result;
}
void task(){
  long long a[10000];
  int n = sheldon_all(63, a);
  lls_qsort(a, n);
  n = lls_unique(a, n);
  long long x, y;
  scanf("%lld%lld", &x, &y);
  assert(x <= y);
  int z = lls_count_between(a, n, x, y);
  printf("%d\n", z);
  if (y <= 1000000){
    int z1 = count_sheldon((int)x, (int)y);
    assert(z1 == z);
  }
}
void unit_tests(void){
  unit_test_ones();
  unit_test_ones_zeros();
}
int main(int argc, char **argv){
  unit_tests();
  int x = 'E';
  if (argc > 1)
    x = *argv[1];
  if (x == 'A')
    test_bits();
  else if (x == 'B')
    test_sheldon();
  else if (x == 'C')
    test_sheldon_all_detailed();
  else if (x == 'D')
    test_sheldon_all();
  else if (x == 'E')
    task();
  else
    printf("%c Invalid option.\n", x);
  return 0;
}


