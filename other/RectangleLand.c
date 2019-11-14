#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
typedef long long ll;
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int binarySearch(int*arr, int r, int x){
  r--;
  int l = 0;
  while(l <= r){
    int m = l + (r-l)/2;
    if(arr[m] == x)
      return m;
    if(arr[m] < x)
      l = m + 1;
    else
      r = m - 1;
  }
  return -1;
}

///////////////////////////////////////////////

typedef struct Snode {
    struct Snode*left;
    struct Snode*right;
    ll    maxSum;
    ll    lazyAdd;
    int   leftNum;
    int   rightNum;
    ll    maxSumVolume;
}Snode;

Snode*newSnode2(int Num, vec*yIndex){
    Snode*rv = calloc(1, sizeof(Snode));
    rv->maxSumVolume = (Num+1 < yIndex->sz)?yIndex->ptr[Num+1] - yIndex->ptr[Num]:0;
    rv->left         = NULL;
    rv->right        = NULL;
    rv->maxSum       = 0;
    rv->lazyAdd      = 0;
    rv->leftNum      = Num;
    rv->rightNum     = Num;
    return rv;
}
Snode*newSnode(int leftX, int rightX, vec*yIndex){
    Snode*rv = calloc(1, sizeof(Snode));
    rv->maxSumVolume = (rightX+1 < yIndex->sz && leftX < yIndex->sz) ? yIndex->ptr[rightX+1] - yIndex->ptr[leftX]:0;
    rv->left         = NULL;
    rv->right        = NULL;
    rv->maxSum       = 0;
    rv->lazyAdd      = 0;
    rv->leftNum      = leftX;
    rv->rightNum     = rightX;
    if(rightX - leftX > 1){
        rv->left  = newSnode(leftX, leftX + (rightX - leftX) / 2, yIndex);
        rv->right = newSnode(leftX + (rightX - leftX) / 2 + 1, rightX, yIndex);
    }
    else{
        rv->left  = newSnode2(leftX,  yIndex);
        rv->right = newSnode2(rightX, yIndex);
    }
    return rv;
}
ll getMax(Snode*sn){
    return sn->maxSum;
}
ll getMaxArea(Snode*sn){
    return sn->maxSumVolume;
}
void rangeAddUpdate(Snode*sn, int x, int y){
    sn->maxSum = fmax(sn->right->maxSum + sn->right->lazyAdd, sn->left->maxSum + sn->left->lazyAdd);
    sn->maxSumVolume = (((sn->right->maxSum + sn->right->lazyAdd) == sn->maxSum) ? sn->right->maxSumVolume:0) +  (((sn->left->maxSum + sn->left->lazyAdd) == sn->maxSum) ? sn->left->maxSumVolume:0);
}
void rangeAdd(Snode*sn, int x, int y, int value){
    if(x <= sn->leftNum && y >= sn->rightNum){
        sn->lazyAdd += value;
        return;
    }
    if((sn->left == NULL && sn->right == NULL) || x > sn->rightNum || y < sn->leftNum)
        return;
    rangeAdd(sn->left , x, y, value);
    rangeAdd(sn->right, x, y, value);
    rangeAddUpdate(sn, x, y);
}

/////////////////////--end-of-Snode----
typedef struct Quad{
    int x, yStart, yEnd, payload;
}Quad;
Quad newQuad(int x, int ys, int ye, int p){
    return(Quad){x, ys, ye, p};
}
int cmpQ(const void*pa, const void*pb){
    Quad*arg0=(Quad*)pa;
    Quad*arg1=(Quad*)pb;
    return arg0->x - arg1->x;
}

int main(){
    int numCases = in_nextInt();
    for(int cases=0; cases<numCases; cases++){
        int numberOfRect = in_nextInt();
        Quad Storage[numberOfRect*2];
        vec yValues = newVec();
        for(int a=0; a<numberOfRect; a++){
            int xS = in_nextInt();
            int yS = in_nextInt();
            int xE = in_nextInt();
            int yE = in_nextInt();
            int payload = in_nextInt();
            Storage[2 * a] = newQuad(xS, yS, yE,    payload);
            Storage[2*a+1] = newQuad(xE, yS, yE, -1*payload);
            pb(yValues, yE);
            pb(yValues, yS);
        }
        qsort(yValues.ptr, yValues.sz, sizeof(int), cmp);
        for(int a=0; a<2*numberOfRect; a++){
            Storage[a].yStart = binarySearch(yValues.ptr, yValues.sz, Storage[a].yStart);
            Storage[a].yEnd   = binarySearch(yValues.ptr, yValues.sz, Storage[a].yEnd);
        }
        qsort(Storage, numberOfRect*2, sizeof(Quad), cmpQ);
        Snode*bigTree = newSnode(0, 262143, &yValues);
        ll max     =-1;
        ll maxArea = 0;
        for(int a=0; a<numberOfRect*2; a++){
            rangeAdd(bigTree, Storage[a].yStart, Storage[a].yEnd-1, Storage[a].payload);
            if(max < getMax(bigTree) && (Storage[a + 1].x - Storage[a].x) != 0){
                maxArea = getMaxArea(bigTree) * ((ll)(Storage[a + 1].x - Storage[a].x));
                max = getMax(bigTree);
            }
            else if (max == getMax(bigTree))
                maxArea += getMaxArea(bigTree) * ((ll)(Storage[a + 1].x - Storage[a].x));
        }
        printf("%lld %lld\n", max, maxArea);
    }
    return 0;
}
