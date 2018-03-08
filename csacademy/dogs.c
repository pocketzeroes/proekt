#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

enum{ MAX =(int) 1e5+5};
int t[MAX*2];
int n,m;

typedef struct{
    int l, r, i;
}group;
group newGroup(int a, int b, int c){
    group rez;
    rez.l=a;
    rez.r=b;
    rez.i=c;
    return rez;
}
group*v;


void build(){
    for(int i = n-1; i > 0; i--)
        t[i] = max(t[i << 1], t[i << 1 | 1]);
}
int query(int l, int r){
    if(r < l)
        return 0;
    int ans = 0;
    for(l += n, r += n; l <= r; l = (l+1) >> 1, r = (r-1) >> 1){
        if(  l & 1 )
            ans = max(ans, t[l]);
        if(!(r & 1))
            ans = max(t[r], ans);
    }
    return ans;
}
int cmpG(const void*pa, const void*pb){ 
    group*ptr_p =(group*)pa; 
    group*ptr_q =(group*)pb;
    group p = *ptr_p;
    group q = *ptr_q;
    if(p.l <= q.r && q.l <= p.r){
        int l = max(p.l, q.l);
        int r = min(p.r, q.r);
        if(l == p.l){
            return (query(r+1, p.r) <= query(q.l, l-1))?-1:1;
        }
        else{
            return (query(p.l, l-1) <= query(r+1, q.r))?-1:1;
        }
    }
    else{
        return (query(p.l, p.r) <= query(q.l, q.r))?-1:1;
    }
}
int main(){
    int l, r;
    while(scanf("%d", &n)==1){
        for(int i = 0; i < n; i++)
            scanf("%d", &t[i+n]);
        build();
        scanf("%d", &m);
        v = calloc(m, sizeof(group));
        for(int i = 0; i < m; i++){
            scanf("%d %d", &l, &r); 
            l--, r--;
            v[i] = newGroup(l, r, i+1);
        }
        qsort(v, m, sizeof(group), cmpG);
        for(int z=0;z<m;z++){int p = v[z].i;
            printf("%d ", p);
        }
        puts("");
    }
    return 0;
}
