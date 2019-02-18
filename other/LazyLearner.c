#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first == b->first)return (a->second < b->second)?-1:1;
  return (a->first < b->first)?-1:1;
}

typedef long long ll;
int n, num;
int m;
int _next[510][26];

typedef struct query{
    int l, r, k, id;
    int ans;
}query;
query q[300010 ];
int   R[20010  ];
pair  x[20010  ];
int   t[20010*4];


char gst [100000];
char buff[100000];
char*s[20010];

int cmp(const void*pa, const void*pb){
    query*qa=(query*)pa;
    query*qb=(query*)pb;
    query a = *qa;
    query b = *qb;
    return(a.l < b.l || (a.l == b.l && a.r < b.r))?-1:1;
}
int cmpAns(const void*pa, const void*pb){
    query*qa=(query*)pa;
    query*qb=(query*)pb;
    query a = *qa;
    query b = *qb;
    return(a.id < b.id)?-1:1;
}
void initNext(){
    for(int i=0; i<=25; i++)
        _next[m][i] = m;
    for(int i=(m - 1); i>=0; i--){
        for(int c=0; c<=25; c++)
            _next[i][c] = _next[i+1][c];
        _next[i][(int)(gst[i] - 'a')] = i;
    }
}
void initLeft(int l){
    for(int i=1; i<=n; i++){
        int id = l - 1;
        int si_size = strlen(s[i]);
        for(int j=0; j<si_size; j++){
            id = _next[id][s[i][j] - 'a'];
            if(j<si_size - 1)
                id++;
            if(id >= m)
                break;
        }
        R[i] = min(id + 1, m + 1);
    }
}
void update(int i, int lo, int hi, int u){
    if (lo > u || hi < u)
        return;
    if (lo == hi){
        t[i]++;
        return;
    }
    update(i * 2, lo, ((lo + hi)>>1), u);
    update(i * 2 + 1, ((lo + hi)>>1) + 1, hi, u);
    t[i] = t[i*2] + t[i*2+1];
}
int get(int i, int lo, int hi, int k){
    if (t[i] < k)
        return -1;
    if (lo == hi)
        return lo;
    if (t[i*2] >= k)
        return get(i * 2, lo, ((lo + hi)>>1), k);
    return get(i * 2 + 1, ((lo + hi)>>1) + 1, hi, k - t[i*2]);
}
int main(int LazyLearner, char**argv){
    scanf("%s", &gst);
    m = strlen(gst);
    scanf("%d %d", &n, &num);
    for(int i=1; i<=n; i++){
        scanf("%s", &buff);
        s[i] = strdup(buff);
    }
    qsort(s+1, n, sizeof(char*), cmpstr);
    for(int i=1; i<=num; i++){
        scanf("%d %d %d", &q[i].l, &q[i].r, &q[i].k);
        q[i].id = i;
    }
    qsort(q+1, num, sizeof(query), cmp);
    initNext();
    int curR;
    for(int i=1; i<=num; i++){
        if(i == 1 || q[i].l != q[i-1].l){
            initLeft(q[i].l);
            curR = 0;
            for(int i=1; i<=n; i++){
                x[i].first = R[i];
                x[i].second = i;
            }
            qsort(x+1, n, sizeof(pair), cmpP);
            for(int i=1; i<=(4 * n); i++)
                t[i] = 0;
        }
        while (curR < n && x[curR + 1].first <= q[i].r){
            ++curR;
            update(1, 1, n, x[curR].second);
        }
        q[i].ans = get(1, 1, n, q[i].k);
    }
    qsort(q+1, num, sizeof(query), cmpAns);
    for(int i=1; i<=n; i++){
        if(strlen(s[i]) > 10)
           s[i][10] = '\0';
    }
    for(int i=1; i<=num; i++){
        if(q[i].ans == -1)
            puts("NO SUCH WORD");
        else
            puts(s[q[i].ans]);
    }
    return 0;
}

