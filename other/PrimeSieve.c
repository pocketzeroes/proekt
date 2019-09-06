#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
enum{ MAX_PRIMES=100000000};
char nums[MAX_PRIMES/8];

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
void sieve(int n){
  memset(nums, 0xff, sizeof(nums));
  bitset_unset(nums, 0);
  bitset_unset(nums, 1);
  for(int i=2; i<=sqrt(n)+1; i++)
    if(bitset_isset(nums, i))
      for(int j=i*i; j<n+2; j+=i)
        bitset_unset(nums, j);
}
int main(){
  int n, q, x, total=0;
  scanf("%d %d", &n, &q);
  sieve(n);
  for(int i=2; i<=n; i++)
    if(bitset_isset(nums,i))
      total++;
  printf("%d\n", total);
  for(int i=0; i<q; i++){
    scanf("%d", &x);
    if(bitset_isset(nums, x))
      puts("1");
    else
      puts("0");
  }
  return 0;
}
