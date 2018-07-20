#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef struct{
  ll first;
  ll second;
}pair;
pair newPair(ll a, ll b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first ) return (a->first  < b->first )?-1:1;
  if(a->second != b->second) return (a->second < b->second)?-1:1;
  return 0;
}
int compP(pair a, pair b){
  if(a.first  != b.first )return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}



enum{ MAXN = 270000};

typedef struct{
	int l, r;
	int val;
}node;
node tree[40 * MAXN];
int  root[MAXN];
int  piv;
vecp qry[MAXN];
vec  nodes[20];
int  n, q, m = (1<<18);
int  cnt   [MAXN * 3];
int  renpos[MAXN * 3];


int newNode(int d){
	nodes[d].ptr = pushback(nodes[d].ptr, &nodes[d].sz, ++piv);
	return piv;
}
void init(int s, int e, int p, int d){
	if(s == e)
    return;
	int m = (s+e)/2;
	tree[p].l = newNode(d + 1);
	tree[p].r = newNode(d + 1);
	init(s  , m, tree[p].l, d + 1);
	init(m+1, e, tree[p].r, d + 1);
}
void upd(int pos, int val, int s, int e, int prv, int nxt, int d){
	if(s == e){
		tree[nxt].val = val;
		return;
	}
	int m = (s+e)/2;
	if(pos <= m){
		tree[nxt].l = newNode(d+1);
		tree[nxt].r = tree[prv].r;
		upd(pos, val, s, m, tree[prv].l, tree[nxt].l, d+1);
	}
	else{
		tree[nxt].l = tree[prv].l;
		tree[nxt].r = newNode(d+1);
		upd(pos, val, m+1, e, tree[prv].r, tree[nxt].r, d+1);
	}
}
pair sons(int v){
	return newPair(tree[tree[v].l].val, tree[tree[v].r].val);
}
void count_sort(int d){
	vecp nxt = newVecP();
	for(int z=0; z<nodes[d].sz; z++){int i = nodes[d].ptr[z];
		nxt.ptr = pushbackP(nxt.ptr, &nxt.sz, sons(i));
	}
	for(int z=0; z<nxt.sz; z++){pair i=nxt.ptr[z];
		cnt[i.second]++;
	}
	for(int i=1; i<3*MAXN; i++){
		cnt[i] += cnt[i-1];
	}
	for(int i=nxt.sz-1; i>=0; i--){
		renpos[--cnt[nxt.ptr[i].second]] = nodes[d].ptr[i];
	}
	for(int i=0; i<nodes[d].sz; i++){
		nodes[d].ptr[i] = renpos[i];
	}
	memset(cnt, 0, sizeof(cnt));
	nxt.sz = 0;
	for(int z=0;z<nodes[d].sz;z++){int i = nodes[d].ptr[z];
		nxt.ptr = pushbackP(nxt.ptr, &nxt.sz, sons(i));
	}
	for(int z=0; z<nxt.sz; z++){pair i = nxt.ptr[z];
		cnt[i.first]++;
	}
	for(int i=1; i<3*MAXN; i++){
		cnt[i] += cnt[i-1];
	}
	for(int i=nodes[d].sz-1; i>=0; i--){
		int v = nodes[d].ptr[i];
		renpos[--cnt[nxt.ptr[i].first]] = v;
	}
	for(int i=0; i<nodes[d].sz; i++){
		nodes[d].ptr[i] = renpos[i];
	}
	memset(cnt, 0, sizeof(cnt));
}
int lambda(const void*pa, const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  pair pp1 = newPair(tree[root[*a]].val, *a);
  pair pp2 = newPair(tree[root[*b]].val, *b);
  return cmpP(&pp1, &pp2)<0?-1:1;
}

int main(){
	scanf("%d %*d %d", &n, &q);

	for(int i=0; i<q; i++){
		int s, e, p, v;
		scanf("%d %d %d %d", &s, &e, &p, &v);
		p--;
		qry[s  ].ptr = pushbackP(qry[s  ].ptr, &qry[s  ].sz, newPair(p, v));
		qry[e+1].ptr = pushbackP(qry[e+1].ptr, &qry[e+1].sz, newPair(p, 0));
	}
  
	root[0] = newNode(0);
	init(0, m-1, root[0], 0);
  
	for(int i=1; i<=n; i++){
		qsort(qry[i].ptr, qry[i].sz, sizeof(pair), cmpP);
		int cur = root[i-1];
		for(int z=0; z<qry[i].sz; z++){pair j = qry[i].ptr[z];
			int nxt = newNode(0);
			upd(j.first, j.second, 0, m-1, cur, nxt, 0);
			cur = nxt;
		}
		root[i] = cur;
	}
  
	for(int i=17; i>=0; i--){
		count_sort(i);
		int cnt = 0;
		for(int j=0; j<nodes[i].sz; ){
			int e = j;

			while(e < nodes[i].sz && compP(sons(nodes[i].ptr[j]), sons(nodes[i].ptr[e]))==0){
				tree[nodes[i].ptr[e++]].val = cnt;
			}
      
			cnt++;
			j = e;
		}
	}
	vec ans = newVec();

	for(int i=1; i<=n; i++)
    ans.ptr = pushback(ans.ptr, &ans.sz, i);
	qsort(ans.ptr, ans.sz, sizeof(int), lambda);

	for(int z=0;z<ans.sz;z++){int i = ans.ptr[z];
    printf("%d\n", i);
  }
  return 0;
}

