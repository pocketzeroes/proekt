#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
//////////////////////////////////
vec numbers;
#define bitset_elem(ptr,bit) ((unsigned char *)(ptr))[(bit)/CHAR_BIT]
#define bitset_mask(bit) (1U << ((bit) % CHAR_BIT))
int bitset_isset(void *ptr, int bit){
  return (bitset_elem(ptr,bit) & bitset_mask(bit)) != 0;
}
int bitset_set(void *ptr, int bit){
  unsigned char *b = (unsigned char *)ptr + (bit / CHAR_BIT);
  unsigned char m = bitset_mask(bit);
  if ((*b & m)) return 0;
  *b |= m;
  return 1;
}
int bitset_unset(void *ptr, int bit){
	unsigned char *b = (unsigned char *)ptr + (bit / CHAR_BIT);
	unsigned char m = bitset_mask(bit);
	if ((*b & m) == 0)
    return 0;
	*b &= ~m;
	return 1;
}
typedef long long ll;
enum{ maxn = 10005};
char bit[maxn/8];
vec primes;
void sieve(ll upperbound){
    ll _sieve_size = upperbound + 1;
    memset(bit, 0xff, sizeof(bit));
    bitset_unset(bit, 0);
    bitset_unset(bit, 1);
    for(ll i=2; i<=_sieve_size; i++){
        if(bitset_isset(bit, i)){
            for(ll j=i*i; j<=_sieve_size; j+=i)
                bitset_unset(bit, j);
            pb(primes, i);
        }
    }
}

int main(){
  sieve(maxn);
  int n, b;
  scanf("%d %d", &n, &b);
  bool possible = true;
  if(n > b){
    puts("impossible");
    return 0;
  }
  int sum = 0;
  for(int i=1; i<=n; i++){
    sum += i;
    pb(numbers, i);
  }
  int idx = 0;
  while(primes.ptr[idx] < sum)
    idx++;
  for(int i=n-1; i>=0; i--){
    int rem = primes.ptr[idx] - sum;
    if(b - numbers.ptr[i] >= rem){
      sum += rem;
      numbers.ptr[i] += rem;
      break;
    }
    int add = b - numbers.ptr[i];
    b--;
    sum += add;
    numbers.ptr[i] += add;
  }
  if(sum < primes.ptr[idx])
    puts("impossible");
  else{
    for(int i = 0; i < n; i++){
      for(int j = 0; j < n; j++){
        if(j > 0)
          printf(" ");
        printf("%d", numbers.ptr[(i + j) % n]);
      }
      puts("");
    }
  }
  return 0;
}
