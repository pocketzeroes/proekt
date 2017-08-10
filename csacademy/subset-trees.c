#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct pairS{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
pair *pushbackP(pair *array, int *size, pair value) {
  pair *output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct vecpS {
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}




///////
enum{ MOD  = 1000000000 + 7};
enum{ NMAX = 4000 + 5      };

int N;
int label[NMAX];
vec freq[NMAX];
int dp[NMAX][NMAX];

inline void upd(int*where, int val){
    (*where) += val;
    if(*where >= MOD)
        (*where) -= MOD;
}

int main(){
    scanf("%d", &N);
    for (int i = 1; i <= N; ++ i) {
        int l, r;
        scanf("%d %d", &l, &r);
        freq[l].ptr = pushback(freq[l].ptr, &freq[l].sz ,r);
    }
    for (int i = 1; i <= 4000; ++i)
        label[i] = label[i - 1] + freq[i].sz;
    vecp pairs = newVecP();
    int cnt = 0;
    for (int i = 1; i <= 4000; ++ i){
        for(int z=0; z<freq[i].sz;z++){int it = freq[i].ptr[z];
            ++cnt;
            pairs.ptr = pushbackP(pairs.ptr, &pairs.sz ,newPair(cnt, label[it]));
        }
        freq[i].sz=0;
    }
    for(int z=0;z<pairs.sz;z++){pair it = pairs.ptr[z];
        freq[it.first].ptr = pushback(freq[it.first].ptr, &freq[it.first].sz ,it.second);
        ++dp[it.first + 1][it.second + 1];
    }
    int ans = 0;
    for (int l = 1; l <= 4001; ++l){
        upd(&ans, dp[l][l]);
        for (int r = l + 1; r <= 4001; ++ r)
            if (dp[l][r]){
                upd(&dp[l + 1][r], dp[l][r]);
                for(int z=0; z<freq[l].sz;z++){int it = freq[l].ptr[z];
                    if (it < r)
                        upd(&dp[it + 1][r], dp[l][r]);
                    else
                        upd(&dp[max(l + 1, r)][it + 1], dp[l][r]);
                }
            }
    }
    printf("%d\n", ans);
    return 0;
}






















































