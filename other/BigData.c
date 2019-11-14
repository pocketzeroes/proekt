#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
enum{ MAXN = 1005};
ll _sieve_size;
char bs[128];
vec primes;
int all [MAXN];
int facs[15000];
int dp  [16500];

void sieve(ll upperbound){
    _sieve_size = upperbound + 1;
    memset(bs, 0xff, sizeof(bs));
    bitset_unset(bs, 0);
    bitset_unset(bs, 1);
    for(ll i=2; i<=_sieve_size; i++){
        if(bitset_isset(bs, i)){
            for(ll j=i*i; j<=_sieve_size; j+=i)
                bitset_unset(bs, j);
            pb(primes, i);
        }
    }
}
void checkFac(){
    facs[0] = 0;
    for(int i=1; i<14100; i++){
        for(int j=0; j<primes.sz && primes.ptr[j]<=i; j++){
            if(i%primes.ptr[j] == 0)
                facs[i]++;
        }
    }
}
int main(){
    sieve(MAXN);
    checkFac();
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d", &all[i]);
    clr(dp);
    for(int j=0; j<(1<<n); j++){
        for(int s=0; s<(1<<n); s++){
            if((s&j)==s){
                int sum = 0;
                for(int k=0; k<n; k++){
                    if(s&(1<<k))
                        sum += all[k];
                }
                dp[j] = fmax(dp[j], facs[sum]+dp[j^s]);
            }
        }
    }
    printf("%d\n", dp[(1<<n)-1]);
    return 0;
}
