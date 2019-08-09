#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define ls l,m,rt<<1
#define rs m+1,r,rt<<1|1

typedef long long ll;
enum{ MOD  = 1000000007ll};
enum{ MAXN = 200005ll    };
ll n,m;

typedef struct{
    ll sum,lazy[4];
}node;
node tree[MAXN<<2];
ll sum[4][MAXN];

ll find_val(ll k, ll x){
    if(k == 0)
        return (-1LL*x*x*x + 6*x*x - 11*x + 6) % MOD;
    if(k == 1)
        return (3*x*x - 12*x + 11) % MOD;
    if(k == 2)
        return -3*x + 6;
    return 1;
}
void add(ll*a, ll b){
   *a = (*a + b)%MOD;
    if(*a < 0)
       (*a) += MOD;
}
void pushUp(ll rt){
    tree[rt].sum = (tree[rt<<1].sum + tree[rt<<1|1].sum) % MOD;
}
void pushDown(ll rt,ll l,ll r){
    ll mid = (l+r)/2;
    for(ll i = 0; i<=3; ++i){
        add(&tree[rt<<1].lazy[i],tree[rt].lazy[i]);
        add(&tree[rt<<1|1].lazy[i],tree[rt].lazy[i]);
        add(&tree[rt<<1].sum,tree[rt].lazy[i]*(sum[i][mid]-sum[i][l-1]+MOD));
        add(&tree[rt<<1|1].sum,tree[rt].lazy[i]*(sum[i][r]-sum[i][mid]+MOD));
        tree[rt].lazy[i] = 0;
    }
}
void update(ll L,ll R, ll C,ll l,ll r,ll rt){
    if(l>R||r<L)
        return ;
    if(L<=l&&r<=R){
        for(ll i = 0; i <= 3; ++i){
            ll val = find_val(i,L)*C;
            add(&tree[rt].sum,val*(sum[i][r]-sum[i][l-1]+MOD));
            add(&tree[rt].lazy[i],val);
        }
        return ;
    }
    ll m=(l+r)>>1;
    pushDown(rt,l,r);
    update(L,R,C,ls);
    update(L,R,C,rs);
    pushUp(rt);
}
ll query(int L,int R,int l,int r,int rt){
    if(L<=l&&r<=R)
        return tree[rt].sum;
    int m=(l+r)>>1;
    pushDown(rt,l,r);
    ll ans = 0;
    if(L<=m)
        ans+=query(L,R,ls)%MOD;
    if(R>m)
        ans+=query(L,R,rs)%MOD;
    return ans%MOD;
}
int main(){
    scanf("%lld %lld", &n, &m);
    for(int i = 1; i<=n; ++i){
        sum[0][i] = sum[0][i-1]+1;
        sum[1][i] = (sum[1][i-1]+i)%MOD;
        sum[2][i] = (sum[2][i-1]+1LL*i*i)%MOD;
        sum[3][i] = (sum[3][i-1]+1LL*i*i*i)%MOD;
    }
    ll a,l,r;
    while(m--){
        scanf("%lld %lld %lld", &a, &l, &r);
        if(a==0){
            printf("%lld\n", query(l,r,1,n,1));
        }
        else if(a==1){
            update(l,r,1,1,n,1);
        }
        else if(a==2){
            update(l,r,-1,1,n,1);
        }
    }
    return 0;
}
