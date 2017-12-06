#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;

typedef struct{
   ll  first;
   int second;
}pair;
pair newPair(ll a, int b){
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
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair *array, int *size, pair value) {
    pair *output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP() {
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
char*concat(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}

/////////////////////////////////////

enum{ md =(int) 1e9 + 7};
enum{ hs = 199         };
int n;
pair*a;
vecp s[2][42]; // ll int

void finish(char*x){
    puts(x);
    exit(0);
}
pair find(int v1, int v2){
    int p1 = 0, p2 = 0;
    while (p1 < s[0][v1].sz && p2 < s[1][v2].sz){
        if (s[0][v1].ptr[p1].first < s[1][v2].ptr[p2].first)
            p1++;
        else if (s[0][v1].ptr[p1].first > s[1][v2].ptr[p2].first)
            p2++;
        else
            return newPair(p1, p2);
    }
    return newPair(-1, -1);
}
void calc(int half, int i, int lim, int amd, ll vald, int bit, int mask){// , 0, 0, 1, 0);
    if (i == lim){
        int idx = amd+n/2+1;
        s[half][idx].ptr = pushbackP(s[half][idx].ptr, &s[half][idx].sz, newPair(vald, mask));
    }
    else {
        calc(half, i + 1, lim, amd + 1, vald + a[i].first , bit * 2, mask + bit);
        calc(half, i + 1, lim, amd - 1, vald - a[i].second, bit * 2, mask      );
    }
}
char*de(int mask, int lim){
    char*rtn = strdup("");
    for(int i = 1; strlen(rtn) < lim; i <<= 1)
        if (mask & i)
            rtn = concat(rtn, '0');
        else
            rtn = concat(rtn, '1');
    return rtn;
}
int main(){
    scanf("%d", &n);
    a = calloc(n, sizeof(pair));
    for (int i = 0; i < n; i++)
        scanf("%lld %d", &a[i].first, &a[i].second);
    calc(0, 0, n / 2, 0, 0, 1, 0);
    calc(1, n / 2, n, 0, 0, 1, 0);
    for (int i = 0; i < 42; i++)
        for(int z=0; z<s[0][i].sz; z++)
            s[0][i].ptr[z].first =- s[0][i].ptr[z].first;
    pair rtn;
    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 42; j++)
            qsort(s[i][j].ptr, s[i][j].sz, sizeof(pair), cmpP);
    for (int d = 0; d < 100; d++) {
        for (int i = 0; i < 42 && n + 2 - i - d >= 0; i++) {
            if (n + 2 - i - d < 42) {
                rtn = find(i, n + 2 - i - d);
                if(rtn.first != -1) {
                    printf("%s", de(s[0][i].ptr[rtn.first].second, n / 2));
                    finish(de(s[1][n+2-i-d].ptr[rtn.second].second, n - n / 2));
                }
            }
        }
        for (int i = 0; i < 42 && n + 2 - i + d >= 0; i++) {
            if (n + 2 - i + d < 42) {
                rtn = find(i, n + 2 - i + d);
                if (rtn.first != -1) {
                    printf("%s", de(s[0][i].ptr[rtn.first].second, n / 2));
                    finish(de(s[1][n+2-i+d].ptr[rtn.second].second, n - n / 2));
                }
            }
        }
    }
    finish("-1");
}
