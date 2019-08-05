#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


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
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

vec primes;


static bool isPrime (int n);
static bool divides_factorial (const int n, const int m);
static void prime_sieve (int max_n);
static int get_powers (const unsigned long int n, const int p);

int main (){
    int n, m;
    prime_sieve(50000);
    while (scanf("%d %d", &n, &m) == 2) {
        if (divides_factorial(n, m)) {
            printf("%d divides %d!\n", m, n);
        }
        else {
            printf("%d does not divide %d!\n", m, n);
        }
    }
    return EXIT_SUCCESS;
}
static bool divides_factorial (const int n, const int m) {
    if (m == 0) {
        return false;
    }
    else if (n >= m) {
        return true;
    }
    else {
        int k = m;
        vecp factors = newVecP();
        for (int i = 0; i < primes.sz; i++){
            if (primes.ptr[i] > k)
                break;
            else{
                pair f =(pair){primes.ptr[i], 0};
                while (k % primes.ptr[i] == 0) {
                    f.second += 1;
                    k = k / primes.ptr[i];
                }
                if (f.second)
                    factors.ptr = pushbackP(factors.ptr, &factors.sz, f);
            }
        }
        if (k > 1) {
            if (n < k)
                return false;
            else
                factors.ptr = pushbackP(factors.ptr, &factors.sz, (pair){k, 1});
        }
        for (int i = 0; i < factors.sz; i++)
            if (factors.ptr[i].second - get_powers(n, factors.ptr[i].first) > 0)
                return false;
        return true;
    }
}
static bool isPrime (int n) {
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}
static void prime_sieve (int max_n) {
    for (int i = 2; i < max_n; i++) {
        if (isPrime(i)) {
            primes.ptr = pushback(primes.ptr, &primes.sz, i);
        }
    }
}
static int get_powers (const unsigned long int n, const int p){
    int res = 0;
    for (unsigned long int power = p; power <= n; power *= p) {
        res += n / power;
    }
    return res;
}
