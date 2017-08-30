#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)

typedef long long ll;
ll min(ll a,ll b){return a<b?a:b;}
ll max(ll a,ll b){return a>b?a:b;}

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
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int unique(int*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
            a[++j] = a[i];
	return j + 1;
}
int lower_bound(int*a, int n, int x) {
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x <= a[mid])
            h = mid;
        else
            l = mid + 1;
    }
    return l;
}




//////////////////////////////
int n;
int a  [100000],
    all[100000], allc = 0;
int fen[100000];
vec v  [100000];
ll le, ri;

void fenAdd(int pos, int val) {
    for (; pos < n; pos |= pos + 1) {
        fen[pos] += val;
    }
}
int fenGet(int pos) {
    int res = 0;
    for (; pos >= 0; pos = (pos & (pos + 1)) - 1) {
        res += fen[pos];
    }
    return res;
}
int getDist(int from, int to) {
    if (from > to)
        swap(from, to);
    return fenGet(to) - fenGet(from - 1) - 1;
}
int main(){
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        scanf("%d", a + i);
    for (int i = 0; i < n; ++i)
        all[i] = a[i];
    qsort(all, n, sizeof(int), cmp);
    allc = unique(all, n);
    for (int i = 0; i < n; ++i)
        a[i] = lower_bound(all, allc, a[i]);
    for (int i = 0; i < n; ++i)
        v[a[i]].ptr = pushback(v[a[i]].ptr, &v[a[i]].sz ,i);
    le = (ll)1e18;
    ri = v[0].ptr[v[0].sz-1] + 1;
    for (int i = 0; i < n; ++i)
        fenAdd(i, 1);
    for(int z=0;z<v[0].sz;z++){int x = v[0].ptr[z];
        fenAdd(x, -1);
    }
    for(int i = 1; i < allc; ++i){
        int from = v[i].ptr[0];
        int to   = v[i].ptr[v[i].sz-1];
        ll  nle  = (ll)1e18;
        ll  nri  = (ll)1e18;
        for(int j = 0; j < 2; ++j){
            int ind = v[i - 1].ptr[0];
            if (j == 1)
                ind = v[i-1].ptr[v[i-1].sz-1];
            int lb = lower_bound(v[i].ptr, v[i].sz, ind);
            ll val = le;
            if (j == 1)
                val = ri;
            ll cur;
            if (to < ind)
                cur = (ll)1e18;
            else if (from > ind)
                cur = val + getDist(ind, to);
            else
                cur = val + getDist(ind, from) + getDist(from, to) - lb + 1;
            nri = min(nri, cur);
            if (from > ind)
                cur = (ll)1e18;
            else if (to < ind)
                cur = val + getDist(ind, from);
            else
                cur = val + getDist(ind, to) + getDist(to, from) - (v[i].sz - lb) + 1;
            nle = min(nle, cur);
        }
        le = nle + 1;
        ri = nri + 1;
        for(int z=0;z<v[i].sz;z++){int x = v[i].ptr[z];
            fenAdd(x, -1);
        }
    }
    printf("%lld\n", min(le, ri));
    return 0;
}




















































