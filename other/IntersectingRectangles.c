#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
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

typedef struct{
    int first ;
    int second;
    int third ;
    int fourth;
}Event;

Event newEvent(int a, int b, int c, int d){
    Event rez;
    rez.first  = a;
    rez.second = b;
    rez.third  = c;
    rez.fourth = d;
    return rez;
}
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
int cmpE(const void*pa, const void*pb){
    Event*a = (Event*)pa;
    Event*b = (Event*)pb;
    if(a->first  != b->first ) return a->first  - b->first ;
    if(a->second != b->second) return a->second - b->second;
    if(a->third  != b->third ) return a->third  - b->third ;
    return a->fourth - b->fourth;
}

//////////////////////////////////////////////
int gn;
int*data;

void BIT(int pn){
    gn = pn;
    data = calloc(gn+1, sizeof(int));
}
int query1(int x){
    x++;
    int res = 0;
    for (; x > 0; x -= (x & -x))
        res += data[x];
    return res;
}
int query(int x, int y){
    if (x > y)
        return 0;
    return query1(y) - query1(x - 1);
}
void update(int x, int v){
    x += 1;
    for(; x < gn; x += (x & -x))
        data[x] += v;
}

int main(){
    int n;
    scanf("%d", &n);
    vece events = newVecE();
    vec all_x   = newVec();
    vec all_y   = newVec();
    for(int i=0; i<n; ++i){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        events.ptr = pushbackE(events.ptr, &events.sz, newEvent(x1, 0, y1, y2));
        events.ptr = pushbackE(events.ptr, &events.sz, newEvent(x2, 0, y1, y2));
        events.ptr = pushbackE(events.ptr, &events.sz, newEvent(x1, 1, y1, y1));
        events.ptr = pushbackE(events.ptr, &events.sz, newEvent(x1, 1, y2, y2));
        events.ptr = pushbackE(events.ptr, &events.sz, newEvent(x2,-1, y1, y1));
        events.ptr = pushbackE(events.ptr, &events.sz, newEvent(x2,-1, y2, y2));
        all_x.ptr  = pushback(all_x.ptr, &all_x.sz, x1);
        all_x.ptr  = pushback(all_x.ptr, &all_x.sz, x2);
        all_y.ptr  = pushback(all_y.ptr, &all_y.sz, y1);
        all_y.ptr  = pushback(all_y.ptr, &all_y.sz, y2);
    }
    qsort(all_x.ptr, all_x.sz, sizeof(int), cmp);
    qsort(all_y.ptr, all_y.sz, sizeof(int), cmp);
    all_x.sz = unique(all_x.ptr, all_x.sz);
    all_y.sz = unique(all_y.ptr, all_y.sz);
    qsort(events.ptr, events.sz, sizeof(Event), cmpE);
    BIT(all_y.sz);
    bool poss = false;
    for(int z=0; z<events.sz; z++){Event e = events.ptr[z];
        int x  = e.first;
        int op = e.second;
        int y1 = e.third;
        int y2 = e.fourth;
        int j1 = lower_bound(all_y.ptr, all_y.sz, y1);
        if(op == 0){
            int j2 = lower_bound(all_y.ptr, all_y.sz, y2);
            if(query(j1 + 1, j2 - 1)){
                poss = true;
                break;
            }
        }
        else
            update(j1, op);
    }
    printf("%d\n", poss);
    return 0;
}
