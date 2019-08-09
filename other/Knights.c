#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(bool*arr, int sz, bool val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}

typedef long long ll;

ll**newmat(int x, int y){
  ll**rv = calloc(x, sizeof(ll*));
  for(int i=0;i<x;i++)
    rv[i] = calloc(y, sizeof(ll));
  return rv;
}

ll MOD = 1000000009LL;
int self[4] ={
    (1<<0)|(1<<5),
    (1<<1)|(1<<4),
    (1<<2)|(1<<7),
    (1<<3)|(1<<6)
};
int attacks[16][2] ={
    {1<<0, 1<<2},
    {1<<2, 1<<4},
    {1<<4, 1<<6},
    {1<<1, 1<<3},
    {1<<3, 1<<5},
    {1<<5, 1<<7},
    {1<<2, 1<<0},
    {1<<4, 1<<2},
    {1<<6, 1<<4},
    {1<<3, 1<<1},
    {1<<5, 1<<3},
    {1<<7, 1<<5},
    {1<<1, 1<<4},
    {1<<3, 1<<6},
    {1<<5, 1<<0},
    {1<<7, 1<<2}
};
int n, m;
bool*valid;
int nmaps;
typedef ll** mat;

typedef struct{
    int key;
    mat val;
}hm;
hm  arr[1000];
int arrsz;

void put(int k, mat v){
    arr[arrsz++]=(hm){k,v};
}
mat get(int k){
    for(int i=0;i<arrsz;i++)
        if(arr[i].key == k)
          return arr[i].val;
    return NULL;
}
mat ways(int m){
    mat result = get(m);
    if(result==NULL){
        result = newmat(nmaps, nmaps);
        mat m1 = ways( m/2+1 );
        mat m2 = ways( m-m/2+1);
        for( int i=0; i<nmaps; i++){
            if( valid[i] ){
                for( int j=0; j<nmaps; j++){
                    if( valid[j] ){
                        result[i][j] = 0;
                        for( int k=0; k<nmaps; k++){
                            if( valid[k] ){
                                result[i][j] += m1[i][k] * m2[k][j] % MOD;
                                result[i][j] %= MOD;
                            }
                        }
                    }
                }
            }
        }
        put(m, result);
    }
    return result;
}
int main(){
    n = in_nextInt();
    m = in_nextInt();
    nmaps = 1<<(n<<1);
    valid = calloc(nmaps, sizeof(bool));
    fill(valid, nmaps, true);
    for(int i=0; i<nmaps; i++)
        for(int j=0; j<4; j++)
            valid[i] &= ((i&self[j])!=self[j]);
    bool compatible[nmaps][nmaps]; memset(compatible, 0, sizeof(compatible));
    for(int i=0; i<nmaps; i++){
        for(int j=0; j<nmaps; j++){
            compatible[i][j] = valid[i] && valid[j];
            for(int k=0; k<16; k++)
                compatible[i][j] &= ((i&attacks[k][0])==0) || ((j&attacks[k][1])==0);
        }
    }
    mat threes = newmat(nmaps, nmaps);
    mat fours  = newmat(nmaps, nmaps);
    int map = 0x55;
    for( int i=0; i<nmaps; i++){
        for( int j=0; j<nmaps; j++){
            fours [i][j] = compatible[i][j] ? 1LL : 0LL;
            threes[i][j] = ((i>>1)&map)==(j&map) && compatible[i][(j>>1)&map] ? 1LL : 0LL;
        }
    }
    put(3, threes);
    put(4, fours );
    ll answer = 0LL;
    if( m==1 )
        answer = 1<<n;
    else if(m==2){
        for(int i=0; i<nmaps; i++ )
            if(valid[i])
                ++answer;
    }
    else{
        mat result = ways( m );
        for(int i=0; i<nmaps; i++){
            if(valid[i]){
                for(int j=0; j<nmaps; j++){
                    if(valid[j]){
                        answer += result[i][j];
                        answer %= MOD;
                    }
                }
            }
        }
    }
    printf("%lld\n", answer);
    return 0;
}
