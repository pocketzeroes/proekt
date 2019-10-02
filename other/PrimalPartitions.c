#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
#define fill(arr, sz, val)do{     \
  for(int i=0; i<sz; i++)         \
    arr[i] = val;                 \
}while(0)
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
//////////////////////
int primes[168];

void generatePrimes(){
    bool isprime[1001]; fill(isprime, 1001, true);
    isprime[0] = false;
    isprime[1] = false;
    int index = 0;
    for(int i=0; i<1001; i++){
        if(isprime[i]){
            primes[index++] = i;
            for(int j=i+i; j<1001; j+=i)
                isprime[j] = false;
        }
    }
}
int gcd(int a, int b){
    return b==0 ? a : gcd( b, a%b );
}
int main(){
    generatePrimes();
    int*biggestprime = calloc(1000001, sizeof(int));
    biggestprime[0] = biggestprime[1] = 0;
    for(int i=2; i<1000001; i++){
        int value = i;
        for( int j=0; j<168 && value>1; j++){
            int p = primes[j];
            if(value%p==0){
                biggestprime[i] = p;
                while(value%p==0)
                    value /= p;
            }
        }
        if(value>1)
            biggestprime[i] = i;
    }
    int n = in_nextInt();
    int k = in_nextInt();
    int sequence[n]; clr(sequence);
    for(int i=0; i<n; i++)
        sequence[i] = in_nextInt();
    int smallest[n][k+1]; clr(smallest);
    int sets    [n][k+1]; clr(sets    );
    fill(smallest[0], k+1, 0);
    fill(sets    [0], k+1, 0);
    smallest[0][1] = biggestprime[sequence[0]];
    sets[0][1] = sequence[0];
    for(int i=1; i<n; i++){
        for(int j=1; j<=k; j++){
            int bestset   = 0;
            int bestscore = 0;
            if(sets[i-1][j]>0){
                bestset = gcd( sets[i-1][j], sequence[i] );
                bestscore = fmin(smallest[i-1][j], biggestprime[bestset]);
            }
            if(sets[i-1][j-1]>0){
                int score = fmin( smallest[i-1][j-1], biggestprime[sequence[i]] );
                if(score > bestscore || bestset==0){
                    bestscore = score;
                    bestset = sequence[i];
                }
            }
            smallest[i][j] = bestscore;
            sets[i][j] = bestset;
        }
    }
    free(biggestprime);
    printf("%d\n", smallest[n-1][k] );
    return 0;
}
