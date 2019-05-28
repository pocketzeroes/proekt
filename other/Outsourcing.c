#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
////////////////
enum{ MAX = 250};

int  numAS     [2],
     numTS     [2],
     numOp     [2];
vecp adjList   [2][MAX];
vec  revList   [2][MAX];
bool productive[2][MAX],
     traversed [MAX][MAX];

void prod(int factory, int node){
    if (productive[factory][node])
        return;
    productive[factory][node] = true;
    for (int i = (0); i <((int)((revList[factory][node]).sz)); i++)
        prod(factory, revList[factory][node].ptr[i]);
}
bool same(int left, int right){
    if (left == numTS[0] - 1 && right != numTS[1] - 1)
        return false;
    if (left != numTS[0] - 1 && right == numTS[1] - 1)
        return false;
    if (traversed[left][right])
        return true;
    traversed[left][right] = true;
    int leftP  = 0;
    int rightP = 0;
    while(true){
        while (leftP < (int)((adjList[0][left]).sz) && !productive[0][adjList[0][left].ptr[leftP].second])
            leftP++;
        while (rightP < (int)((adjList[1][right]).sz) && !productive[1][adjList[1][right].ptr[rightP].second])
            rightP++;
        if (leftP >= (int)((adjList[0][left]).sz) && rightP < (int)((adjList[1][right]).sz))
            return false;
        if (leftP < (int)((adjList[0][left]).sz) && rightP >= (int)((adjList[1][right]).sz))
            return false;
        if (leftP >= (int)((adjList[0][left]).sz) && rightP >= (int)((adjList[1][right]).sz))
            return true;
        if (adjList[0][left].ptr[leftP].first != adjList[1][right].ptr[rightP].first)
            return false;
        if (!same(adjList[0][left].ptr[leftP].second, adjList[1][right].ptr[rightP].second))
            return false;
        leftP++, rightP++;
    }
}
int main(){
    int numCases, from, to, label;
    scanf("%d", &numCases);
    while (numCases-- > 0){
        for (int i = (0); i < (2); i++) {
            scanf("%d %d %d", numAS+i, numTS+i, numOp+i);
            for (int j = (0); j < (numTS[i]); j++) {
                adjList[i][j].sz=0;
                revList[i][j].sz=0;
                productive[i][j] = false;
            }
        }
        for (int i = (0); i < (numTS[0]); i++)
            for (int j = (0); j < (numTS[1]); j++)
                traversed[i][j] = false;
        for (int i = (0); i < (2); i++){
            for (int j = (0); j < (numAS[i]); j++){
                scanf("%d %d %d", &from, &to, &label);
                pair next = (pair){label, to};
                adjList[i][from].ptr = pushbackP(adjList[i][from].ptr, &adjList[i][from].sz, next);
                revList[i][to  ].ptr = pushback(revList[i][to].ptr, &revList[i][to].sz, from);
            }
            for (int j = (0); j < (numTS[i]); j++)
                qsort(adjList[i][j].ptr, adjList[i][j].sz, sizeof(pair), cmpP);
            prod(i, numTS[i] - 1);
        }
        printf("%s\n", same(0,0) ? "eligible" : "not eligible");
    }
    return 0;
}
