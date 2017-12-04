#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
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
/////////////////////////////////////////////////////

enum{ SIZE = 1 << 10};
int pointer = SIZE;
char buffer[SIZE];
enum{ CELLS = 25      };
enum{ INF = 1000000000};
int value[CELLS], v[CELLS];
char seen[(1<<CELLS)/8]; //33554432
pair temp[CELLS];
int dp[1 << CELLS];
int neighbour[30]={35, 71, 142, 284, 536, 1121, 2274, 4548, 9096, 17168, 35872, 72768, 145536, 291072, 549376, 1147904, 2328576, 4657152, 9314304, 17580032, 3178496, 7405568, 14811136, 29622272, 25690112};
int inside[9]={6, 7, 8, 11, 12, 13, 16, 17, 18};

int Solve(int mask){
    if(bitset_isset(seen, mask))
        return dp[mask];
    bitset_set(seen, mask);
    int bad = 0;
    for(int i = 0; i < 9; i++)
        if((neighbour[inside[i]] & mask) == neighbour[inside[i]])
            bad |= 1 << inside[i];
    if(!bad){
        dp[mask] = 0;
        int sign = 1;
        for (int i = 0; i < 25; i++)
            if (mask & (1 << v[i])) {
                dp[mask] += sign * value[v[i]];
                sign *= -1;
            }
        return dp[mask];
    }
    int good = mask - bad, w[25], state[25], n = 0;
    for(int i = 0, j = 1; i < 25; i++, j *= 2)
        if(good & j){
            int k = 0, now = neighbour[i] & bad;
            while (k < n && now != state[k])
                k++;
            if (k == n) {
                w[n] = i;
                state[n] = now;
                n++;
            }
            else
                if (value[i] > value[w[k]])
                    w[k] = i;
        }
    dp[mask] = -INF;
    for(int i = 0; i < n; i++)
        dp[mask] = max(dp[mask], value[w[i]] - Solve(mask ^ (1 << w[i])));
    return dp[mask];
}
int main(){
    int tests;
    scanf("%d", &tests);
    for(int test = 1; test <= tests; test++){
        memset(seen, 0, sizeof(seen));
        bitset_set(seen, 0);
        int sum = 0;
        for (int i = 0; i < CELLS; i++){
            scanf("%d", &value[i]);
            temp[i] = newPair(value[i], i);
            sum += value[i];
        }
        qsort(temp, CELLS, sizeof(pair), cmpP);
        for (int i = 0; i < CELLS; i++)
            v[i] = temp[CELLS - i - 1].second;
        printf("%d\n", (sum + Solve((1 << CELLS) - 1)) / 2);
    }
    return 0;
}

