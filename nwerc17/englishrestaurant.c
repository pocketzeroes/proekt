#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}
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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////
typedef long double ld;

int n2(int n) { 
    return n * (n + 1) / 2; 
}
void fadd(ld*a, ld*b, ld p, ld q){
   *a = *a *q + *b * p;
   *b = *b *q;
}
pair rfrac(int l, int r, vec*c, int g){
    int minel = l > 0 ? c->ptr[l - 1] : 0;
    int lb = min(g, minel);
    int rb = min(g, c->ptr[r]);
    return newPair(c->ptr[r] <= 211 ? n2(rb) - n2(lb) : 0, rb - lb);
}
int main(){
    int n, g, t;
    scanf("%d %d %d", &n, &g, &t);
    vec c = newVec();
    for(int i=0; i<n; i++){
        int val;
        scanf("%d", &val);
        c.ptr = pushback(c.ptr, &c.sz, val);
    }
    qsort(c.ptr, c.sz, sizeof(int), cmp);
    for(int i = 0; i < t; ++i){
        c.ptr = pushback(c.ptr, &c.sz, 300);
        ++n;
    }
    ld nCk[212][212];
    for (int i = 0; i <= 211; ++i)
        nCk[0][i] = 0, nCk[i][0] = 1;
    for (int i = 1; i <= 211; ++i)
        for (int j = 1; j <= 211; ++j)
            nCk[i][j] = nCk[i-1][j-1] + nCk[i-1][j];
    ld num[211][211], den[211][211];
    for (int r = 0; r < n; ++r){
        pair rv = rfrac(r, r, &c, g);
        num[r][r] = rv.first; 
        den[r][r] = rv.second;
        for (int l = r - 1; l >= 0; --l){
            num[l][r] = 0;
            den[l][r] = 0;
            for (int k = l; k <= r; ++k){
                ld sum = 0.0;
                ld ways = nCk[r-l][k-l];
                ld a, b;
                pair rv = rfrac(l, k, &c, g);
                a = rv.first;
                b = rv.second;
                fadd(&sum, &ways, a, b);
                if (l < k) 
                    fadd(&sum, &ways, num[l][k-1], den[l][k-1]);
                if (k < r) 
                    fadd(&sum, &ways, num[k+1][r], den[k+1][r]);
                num[l][r] += sum;
                den[l][r] += ways;
            }
        }
    }
    ld dpn[211][211], dpd[211][211];
    for (int i = 0; i < 211; ++i)
        for (int j = 0; j < 211; ++j)
            dpn[i][j] = dpd[i][j] = 0;
    for (int i = t - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (t-i <= n-j) {
                dpn[i][j] = num[j][j+t-i-1];
                dpd[i][j] = den[j][j+t-i-1];
            }
        }
    }
    for (int i = t - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            for (int ni = i + 1; ni < t; ++ni) {
                for (int ns = j + (ni-i) + 1; ns < n; ++ns) {
                    ld sum = 0.0, ways = nCk[t-i][t-ni];
                    fadd(&sum, &ways, num[j][j+(ni-i)-1], den[j][j+(ni-i)-1]);
                    fadd(&sum, &ways, dpn[ni][ns], dpd[ni][ns]);
                    dpn[i][j] += sum;
                    dpd[i][j] += ways;
                }
            }
        }
    }
    ld ansn = 0.0, ansd = 0.0;
    for (int l = 0; l < n; ++l)
        ansn += dpn[0][l], ansd += dpd[0][l];
    printf("%.12lf\n", (double)(ansn / ansd));
    return 0;
}
