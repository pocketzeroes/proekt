#pragma GCC optimize "-O4"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#ifdef _WIN32
  #define inline static
#endif
inline double min(double a,double b) {
    return a<b?a:b;
}
inline double max(double a,double b) {
    return a>b?a:b;
}
typedef struct pair {
    double first;
    int    second;
} pair;
inline pair newPair(double a, int b) {
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
typedef long long LL;
enum { N = 1010};
const double inf = 1e7;
int n, m, S, T;
typedef struct edgeS {
    int to,
        pre;
    double c;
} edge;
edge e[N << 1];
int u[N], l = 0;
double f[N];
int q[N], d[N];
const double eps = 1e-9;
double out[N];
int ol, sl;
double c[N];
int cl;
pair od[N * N];
int odl;



inline void swap(int*nums, int i, int j) {
    int t   = nums[i];
    nums[i] = nums[j];
    nums[j] = t;
}
void reverse(int*nums,int start,int end) {
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
inline int compP(pair a, pair b) {
	if(a.first != b.first)
	  return a.first > b.first?1:-1;
	return a.second - b.second;
}
int cmp(const void*pb,const void*pa){
  double*a=(double*)pa;
  double*b=(double*)pb;
  return a[0] < b[0];
}
int cmpP(const void*pa, const void*pb){
  pair*ptra=(pair*)pa;
  pair*ptrb=(pair*)pb;
  pair a = *ptra;
  pair b = *ptrb;
  return compP(a, b);
}
void merge(pair*b, int n, pair*a, int m, pair*sorted) {
    int i, j, k;
    j = k = 0;
    for (i = 0; i < m + n;) {
        if (j < m && k < n) {
            if(compP(a[j] , b[k]) < 0)
                sorted[i] = a[j++];
            else 
                sorted[i] = b[k++];
            i++;
        }
        else if (j == m) {
            for (; i < m + n;) 
                sorted[i++] = b[k++];
        }
        else {
            for (; i < m + n;) 
                sorted[i++] = a[j++];
        }
    }
}
/////
inline void ins(int a, int b, double c) {
    e[++l] = (edge) {b, u[a], c}, u[a] = l;
}
void mysort(){
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) 
        if (!d[i]) 
            q[r++] = i;
    while (l < r) {
        int x = q[l++];
        for(int i = u[x]; i; i = e[i].pre) 
            if (e[i].to != x) {
                d[e[i].to]--;
                if (!d[e[i].to]) 
                    q[r++] = e[i].to;
            }
    }
    reverse(q, 1, n);
}
void init(int x) {
    ol = 0, sl = 0, cl = 0, odl = 0;
    for(int i = u[x]; i; i = e[i].pre) {
        c[++cl] = e[i].c;
        if (e[i].to == x) 
            ++sl;
        else 
            out[++ol] = f[e[i].to];
    }
    qsort(c   + 1, cl, sizeof(double), cmp);
    qsort(out + 1, ol, sizeof(double), cmp);
    for(int i = 1; i <= ol; i++) 
        for(int j = 1; j <= cl; j++) 
            od[++odl] = newPair(out[i] + c[j],i);
    qsort(od+1, odl, sizeof(pair), cmpP);
}
double calc(int x, double m) {
    f[x] = m;
    if (!cl) 
        return f[x] = inf;
    int l = cl;
    int k = 0;
    while (k + 1 <= ol && out[k + 1] < m) 
        k++;
    static pair d[N * N];//memset(d,0,sizeof(d)); 
    static pair t[N * N];//memset(t,0,sizeof(t));
    int tl = 0;
    for(int j = 1; j <= cl; j++) 
        for(int i = 1; i <= sl; i++) 
            t[++tl] = newPair(m + c[j],k + i);
    for(int i = 1; i <= odl; i++) {
        int a = od[i].second;
        a = (a <= k ? a : a + sl);
        od[i].second = a;
    }
    merge(od+1, odl, t+1, tl, d+1);
    for(int i = 1; i <= odl; i++) {
        int a = od[i].second;
        a = (a <= k ? a : a - sl);
        od[i].second=a;
    }
    int dl = odl + tl;
    static int cnt[N];
    for(int i = 1; i <= l; i++) 
        cnt[i] = l;
    double ans = 1, cur = 0, tot = 0;
    for(int i = 1; i <= dl; i++) {
        tot = tot + ans * (d[i].first - cur), cur = d[i].first;
        int x = d[i].second;
        ans = ans / (cnt[x] - (x - 1)) * (cnt[x] - x), cnt[x]--;
        if (ans < eps) 
            break;
    }
    return f[x] = min(tot, inf);
}
void cal(int x) {
    init(x);
    double l = calc(x,0);
    double r = calc(x,inf);
    while (l + eps < r) {
        double mid = (l + r) / 2;
        calc(x, mid);
        if (f[x] > mid) 
            l = mid;
        else 
            r = mid;
    }
    f[x] = (l + r) / 2;
}
int main() {
    scanf("%d %d %d %d", &n, &m, &S, &T);
    for(int i = 1; i <= m; i++){
        int a, b;
        double c;
        scanf("%d %d %lf", &a, &b, &c);
        ins(a, b, c);
        if (a != b) 
            d[b]++;
    }
    mysort();
    for(int i = 1; i <= n; i++) {
        int x = q[i];
        if (x == T) 
            f[x] = 0;
        else{
            cal(x);
        }
    }
    if (f[S] < 1e6) 
        printf("%.10lf\n",f[S]);
    else 
        printf("-1\n");
    return 0;
}











































































