#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
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
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int x  [2000];
int cid[2000];

int steps(int s, int t, int id){
	cid[s] = id;
	if (s == t)
    return 0;
	return 1 + steps(x[s], t, id);
}
int main(){
	int k, n;
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; ++i) 
		scanf("%d", x+i);
	vecp cycles = newVecP();
	memset(cid, -1, sizeof(cid));
	for (int i = 1; i <= n; ++i){
		int at = i;
		int seen[2000] = {0};
		while (!seen[at]) {
			seen[at] = true;
			at = x[at];
		}
		if (cid[at] != -1)
      continue;
		int l = 1 + steps(x[at], at, cycles.sz);
		cycles.ptr = pushbackP(cycles.ptr, &cycles.sz, newPair(l, 0));
	}
	for (int i = 1; i <= n; ++i){
		if (cid[i] == -1) {
			int at = i;
			while (cid[at] == -1)
				at = x[at];
			++cycles.ptr[cid[at]].second;
		}
  }
	int cando[2000];
	memset(cando, 0, sizeof(cando));
	cando[0] = true;
	for(int z=0;z<cycles.sz;z++){pair p = cycles.ptr[z];
		for (int v = k-1; v >= 0; --v){
			if (cando[v])
				for (int x = p.first; x <= k && x <= p.first+p.second; ++x)
					cando[v+x] = true;
		}
	}
	for (int x = k; x>= 0; --x){
		if (cando[x]){
			printf("%d\n", x);
			break;
		}
  }
	return 0;
}
