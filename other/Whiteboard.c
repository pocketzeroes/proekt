#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;

char buff[1000001];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}

int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int highestOneBit(int i){
    i |= (i >>  1);
    i |= (i >>  2);
    i |= (i >>  4);
    i |= (i >>  8);
    i |= (i >> 16);
    return i - (i >> 1);
}
typedef struct{//SegmentTree
    int size;
    int*tree;
    int len;
}SegmentTree;


SegmentTree newSegmentTree(int size){
    SegmentTree this;
    this.size = size;
    int k = highestOneBit(size);
    if(k!=size)
        k<<=1;
    this.tree = calloc(k+k, sizeof(int));
    fill(this.tree, k+k, -1);
    this.len = k+k;
    return this;
}
void put_(SegmentTree*t, int node , int lo, int hi, int lower, int upper, int value){
    if(lower<=lo && hi<=upper)
        t->tree[node] = value;
    else{
        int mid = (hi+lo)/2;
        if(lower<=mid)
            put_(t, node+node, lo, mid, lower, upper, value);
        if(upper>mid)
            put_(t, node+node+1, mid+1, hi, lower, upper, value);
    }
}
void put (SegmentTree*t, int lower, int upper, int value){
    put_(t, 1, 0, t->size-1, lower, upper, value);
}
int  get_(SegmentTree*t, int node , int lo, int hi, int index){
    int result = -1;
    if(node < t->len){
        int mid = (lo+hi)/2;
        result = fmaxl(t->tree[node], (index<=mid) ? get_(t, node+node, lo, mid, index ) : get_(t, node+node+1, mid+1, hi, index));
    }
    return result;
}
int  get (SegmentTree*t, int index){
    return get_(t, 1, 0, t->size-1, index);
}

typedef struct{//Command
    int i, j;
    ll  second;
}Command;
Command newCommand(int i, int j, ll second){
    Command this;
    this.i = i;
    this.j = j;
    this.second = second;
    return this;
}
ll timeAt(Command*c, int i, int j){
    return c->second + abs(c->i - i ) + abs(c->j - j);
}
int main(){
    int h = in_nextInt();
    int w = in_nextInt();
    int n = in_nextInt();
    char*target[h];
    for(int i=0; i<h; i++)
        target[i] = getstr();
    SegmentTree rows[h];
    for(int i=0; i<h; i++)
        rows[i] = newSegmentTree(w);
    SegmentTree cols[w];
    for(int j=0; j<w; j++)
        cols[j] = newSegmentTree(h);
    int i=h-1, j=0;
    ll seconds = 1LL;
    Command commands[n+1];
    commands[0] = newCommand( 0, 0, 1L );
    put(&rows[h-1], 0, 0, 0);
    put(&cols[0], h-1, h-1, 0);
    for(int k=1; k<=n; k++){
        char*dir=getstr();
        char direction = dir[0];
        int distance = in_nextInt();
        commands[k] = newCommand(i, j, seconds);
        switch(direction){
            case 'u' : put(&cols[j], i-distance, i-1, k ); i -= distance; break;
            case 'd' : put(&cols[j], i+1, i+distance, k ); i += distance; break;
            case 'l' : put(&rows[i], j-distance, j-1, k ); j -= distance; break;
            case 'r' : put(&rows[i], j+1, j+distance, k ); j += distance; break;
            default  : fprintf(stderr, "PANIC!! Unknown direction");
        }
        seconds += distance;
    }
    bool impossible = false;
    ll lowest = 0;
    ll highest = seconds;
    for( i=0; i<h; i++){
        for( j=0; j<w; j++){
            int command = fmaxl( get(&rows[i], j), get(&cols[j], i));
            ll mx = command<0 ? -1 : timeAt(&commands[command], i, j);
            if(target[i][j]=='#' ){
                if(mx<0)
                    impossible = true;
                else
                    lowest = fmaxl(lowest, mx);
            }
            else{
                if(mx>0)
                    highest = fminl(highest, mx-1);
            }
        }
    }
    if(highest<lowest)
        impossible = true;
    if(impossible)
        return puts("-1 -1")*0;
    printf("%lld %lld\n", lowest, highest);
    return 0;
}
