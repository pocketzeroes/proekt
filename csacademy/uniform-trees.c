#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define PB push_back  
#define MP make_pair  
#define SZ(v) ((int)(v).size())  
#define FOR(i,a,b) for(int i=(a);i<(b);++i)  
#define REP(i,n) FOR(i,0,n)  
#define FORE(i,a,b) for(int i=(a);i<=(b);++i)  
#define REPE(i,n) FORE(i,0,n)  
#define FORSZ(i,a,v) FOR(i,a,SZ(v))  
#define REPSZ(i,v) REP(i,SZ(v))  
typedef long long ll;
typedef unsigned long long ull;
ll gcd(ll a,ll b) { return b==0?a:gcd(b,a%b); }


enum{ MAXN=200000    };
enum{ MOD =1000000007};
int n;
int par[MAXN];
int v[MAXN];
int chead[MAXN],cnxt[MAXN];
int sz[MAXN];
int sum;
int seen[MAXN];
int cntzero[MAXN];
int mlt[MAXN];
int ans[MAXN];
int ways[MAXN];





void dfssz(int at) {
	sz[at]=1;
	for(int to=chead[at];to!=-1;to=cnxt[to]) {
		dfssz(to);
		sz[at]+=sz[to];
	}
}
void dfsadd(int at) {
	if(++seen[v[at]]==1) {
		if(ways[at]==0) {
			if(++cntzero[v[at]]==1) sum=(sum+MOD-mlt[v[at]])%MOD;
		} else {
			if(cntzero[v[at]]==0) sum=(sum+MOD-mlt[v[at]])%MOD;
			mlt[v[at]]=(ll)mlt[v[at]]*ways[at]%MOD;
			if(cntzero[v[at]]==0) sum=(sum+mlt[v[at]])%MOD;
		}
	}
	for(int to=chead[at];to!=-1;to=cnxt[to]) dfsadd(to);
	--seen[v[at]];
}
int pw(int x,int n) { 
  int ret=1; while(true) { if(n&1) ret=(ll)ret*x%MOD; if((n>>=1)==0) return ret; x=(ll)x*x%MOD; } 
}
void dfsrem(int at) {
	if(++seen[v[at]]==1) {
		if(ways[at]==0) {
			if(--cntzero[v[at]]==0) sum=(sum+mlt[v[at]])%MOD;
		} else {
			if(cntzero[v[at]]==0) sum=(sum+MOD-mlt[v[at]])%MOD;
			mlt[v[at]]=(ll)mlt[v[at]]*pw(ways[at],MOD-2)%MOD;
			if(cntzero[v[at]]==0) sum=(sum+mlt[v[at]])%MOD;
		}
	}
	for(int to=chead[at];to!=-1;to=cnxt[to]) dfsrem(to);
	--seen[v[at]];
}
void dfs(int at,bool keep) {
	int heavy=-1;
	for(int to=chead[at];to!=-1;to=cnxt[to]) if(heavy==-1||sz[to]>sz[heavy]) heavy=to;
	int ret=0;
	for(int to=chead[at];to!=-1;to=cnxt[to]) if(to!=heavy) dfs(to,false);
	if(heavy!=-1) dfs(heavy,true);
	for(int to=chead[at];to!=-1;to=cnxt[to]) if(to!=heavy) dfsadd(to);
	ans[at]=(sum+MOD-(n-1))%MOD;
	ways[at]=(ans[at]+(cntzero[v[at]]==0?mlt[v[at]]:0))%MOD;
	if(!keep) {
		for(int to=chead[at];to!=-1;to=cnxt[to]) dfsrem(to);
	} else {
		if(ways[at]==0) {
			if(++cntzero[v[at]]==0) sum=(sum+MOD-mlt[v[at]])%MOD;
		} else {
			if(cntzero[v[at]]==0) sum=(sum+MOD-mlt[v[at]])%MOD;
			mlt[v[at]]=ways[at];
			if(cntzero[v[at]]==0) sum=(sum+mlt[v[at]])%MOD;
		}
	}
}
void run() {
	scanf("%d",&n);
	REP(i,n) scanf("%d%d",&par[i],&v[i]),--v[i];
	FOR(i,1,n) --par[i];
	REP(i,n) chead[i]=-1; for(int i=n-1;i>=1;--i) cnxt[i]=chead[par[i]],chead[par[i]]=i;
	dfssz(0);
	sum=n; REP(i,n) seen[i]=0,cntzero[i]=0,mlt[i]=1;
	dfs(0,true);
	int ret=0; REP(i,n) ret=(ret+ans[i])%MOD; printf("%d\n",ret);
}
int main() {
	run();
	return 0;
}




























