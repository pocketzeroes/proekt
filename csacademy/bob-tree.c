#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)


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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
/////////////////////
enum{ MAX_N          = 100000     };
enum{ MAX_Q          = 100000     };
enum{ MAX_COL        = 100000     };
enum{ EULER_TOUR     = 2*MAX_N - 1};
enum{ LOG_EULER_TOUR = 18         };
int col[1+MAX_N], lastT[1+MAX_N];
int depth[1+MAX_N];
vec graph[1+MAX_N];
int firstId[1+MAX_N], lastid;
int rmq[LOG_EULER_TOUR][EULER_TOUR],
    mylog[1+EULER_TOUR];
int colorQuery[1+MAX_Q];
int rez[1+MAX_Q];
int xcol[1+MAX_COL], ycol[1+MAX_COL];
typedef struct Event{
	int lt, rt;
	int nod, color;
}Event;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Event*pushbackE(Event*array, int *size, Event value){
  Event*output = resizeArray(array, Event, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Event*ptr;
	int sz;
}vece;
vece newVecE(){
	vece rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct State{
	int color, x, y;
}State;
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
State*pushbackSt(State*array, int *size, State value){
  State*output = resizeArray(array, State, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	State*ptr;
	int sz;
}vecst;
vecst newVecSt(){
	vecst rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


void eulerTour(int root, int papa){
	firstId[root] = lastid;
	rmq[0][lastid++] = root;
	for(int z=0;z<graph[root].sz;z++){int it = graph[root].ptr[z];
		if(it != papa){
			depth[it] = depth[root] + 1;
			eulerTour(it, root);
			rmq[0][lastid++] = root;
		}
  }
}
int getHigher(int a, int b){
	if(depth[a] < depth[b]) 
    return a;
	return b;
}
void buildEulerTourLCA(int n){
	eulerTour(1, 0);
	for(int l = 1; l < LOG_EULER_TOUR; ++l)
		for(int i = 0; i < lastid - (1 << l) + 1; ++i)
			rmq[l][i] = getHigher(rmq[l - 1][i], rmq[l - 1][i + (1 << (l - 1))]);
	for(int i = 2; i <= lastid; ++i)
		mylog[i] = mylog[i / 2] + 1;
}
int queryRmq(int l, int r){
	int s = r - l + 1, lg = mylog[s];
	return getHigher(rmq[lg][l], rmq[lg][r - (1 << lg) + 1]);
}
int getLCA(int a, int b){
	if(firstId[a] > firstId[b])
		swap(a, b);
	return queryRmq(firstId[a], firstId[b]);
}
int getdist(int a, int b){
	int l = getLCA(a, b);
	return depth[a] + depth[b] - 2 * depth[l];
}
void divide(int l, int r, vece*events){
	int mid = (l + r) / 2;
	vece leftEvs = newVecE();
  vece rightEvs= newVecE();
	vecst states = newVecSt();
	for(int z=0;z<events->sz; z++){Event it = events->ptr[z];
		if(it.lt <= l && r <= it.rt) {
			states.ptr = pushbackSt(states.ptr, &states.sz, (State){it.color, xcol[it.color], ycol[it.color]});
			if(xcol[it.color] == 0)
				xcol[it.color] = it.nod;
			else if(ycol[it.color] == 0)
				ycol[it.color] = it.nod;
			else {
				int distXY = getdist(xcol[it.color], ycol[it.color]);
				int distXC = getdist(it.nod, xcol[it.color]);
				int distYC = getdist(it.nod, ycol[it.color]);
				if(distXC > distXY && distXC > distYC)
					ycol[it.color] = it.nod;
				else if(distYC > distXY)
					xcol[it.color] = it.nod;
			}
		} 
    else {
			if(it.lt <= mid)
				leftEvs.ptr = pushbackE(leftEvs.ptr, &leftEvs.sz, it);
			if(mid + 1 <= it.rt)
				rightEvs.ptr = pushbackE(rightEvs.ptr, &rightEvs.sz, it);
		}
	}
	if(l == r && colorQuery[l] != 0)
		rez[l] = getdist(xcol[colorQuery[l]], ycol[colorQuery[l]]);
	else if(l < r) {
		divide(l, mid, &leftEvs);
		divide(mid + 1, r, &rightEvs);
	}
	for(int i = states.sz - 1; i >= 0; --i) {
		xcol[states.ptr[i].color] = states.ptr[i].x;
		ycol[states.ptr[i].color] = states.ptr[i].y;
	}
}
int main(){
	int N, Q;
	vece events = newVecE();
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i)
		scanf("%d", &col[i]);
	for(int i = 0; i < N - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		graph[a].ptr = pushback(graph[a].ptr, &graph[a].sz, b);
		graph[b].ptr = pushback(graph[b].ptr, &graph[b].sz, a);
	}
	buildEulerTourLCA(N);
	scanf("%d", &Q);
	for(int i=0; i<Q; ++i){
		int t, v, c;
		scanf("%d", &t);
		if(t == 1){
			scanf("%d%d", &v, &c);
			events.ptr=pushbackE(events.ptr, &events.sz, (Event){lastT[v], i, v, col[v]});
			col[v] = c;
			lastT[v] = i + 1;
		} 
    else{
			scanf("%d", &c);
			colorQuery[i] = c;
		}
	}
	for(int i = 1; i <= N; ++i)
		if(Q - 1 >= lastT[i])
			events.ptr=pushbackE(events.ptr, &events.sz, (Event){lastT[i], Q - 1, i, col[i]});
	divide(0, Q - 1, &events);
	for(int i = 0; i < Q; ++i)
		if(colorQuery[i] != 0)
			printf("%d\n", rez[i]);
	return 0;
}

