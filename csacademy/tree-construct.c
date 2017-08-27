#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<assert.h>

int min(int a,int b){return a<b?a:b;}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////


enum{ N = 1000100};
int n;
int isFarthest[N];
int p[N];
int ans[N][2];
int ansSz;
vec toV, toU, toNon;

void Fail(){
    printf("Impossible\n");
    exit(0);
}
void printAns(){
    printf("Possible\n");
    for (int i = 0; i < ansSz; i++)
        printf("%d %d\n", ans[i][0] + 1, ans[i][1] + 1);
    exit(0);
}
void addAns(int v, int u) {
    ans[ansSz][0] = v;
    ans[ansSz][1] = u;
    ansSz++;
}
void solveOne(int V){
    if (p[V] != -1) Fail();
    for (int i = 0; i < n; i++) {
        if (p[i] == V)
            toV.ptr = pushback(toV.ptr, &toV.sz ,i);
        else
            toNon.ptr=pushback(toNon.ptr, &toNon.sz ,i);
    }
    int it = 0;
    while(toNon.ptr[it] != V) it++;
    swap(toNon.ptr, 0, it);
    if (toNon.sz < 2) Fail();
    if (toV.sz < 3) Fail();
    if (toNon.sz == 2){
        addAns(toNon.ptr[0], toNon.ptr[1]);
        addAns(toNon.ptr[1], toV  .ptr[0]);
        for (int i = 1; i < toV.sz; i++)
            addAns(toV.ptr[0], toV.ptr[i]);
        printAns();
    }
    addAns(toNon.ptr[0], toNon.ptr[1]);
    addAns(toNon.ptr[1], toNon.ptr[2]);
    for (int i = 3; i < toNon.sz; i++)
        addAns(toNon.ptr[2], toNon.ptr[i]);
    addAns(toNon.ptr[2], toV.ptr[0]);
    for (int i = 1; i < toV.sz; i++)
        addAns(toV.ptr[0], toV.ptr[i]);
    printAns();
}
void solveTwo(int V, int U) {
    if (p[V] != U || p[U] != V) Fail();
    for (int i = 0; i < n; i++) {
        if (p[i] == V)
            toV.ptr = pushback(toV.ptr, &toV.sz ,i);
        else if (p[i] == U)
            toU.ptr = pushback(toU.ptr, &toU.sz ,i);
        else
            toNon.ptr = pushback(toNon.ptr, &toNon.sz ,i);
    }
    int it = 0;
    while(toU.ptr[it] != V) it++;
    swap(toU.ptr, 0, it);
    it = 0;
    while(toV.ptr[it] != U) it++;
    swap(toV.ptr, 0, it);
    int szV = toV.sz, szU = toU.sz;
    if (szV < 3 || szU < 3) {
        if (szV != szU) Fail();
        if (szV == 1 && toNon.sz > 1) Fail();
        for (int i = 1; i < szV; i++)
            addAns(toV.ptr[i - 1], toV.ptr[i]);
        for (int i = 1; i < szU; i++)
            addAns(toU.ptr[i - 1], toU.ptr[i]);
        
    } 
    else {
        addAns(toV.ptr[0], toV.ptr[1]);
        addAns(toV.ptr[1], toV.ptr[2]);
        for (int i = 3; i < szV; i++)
            addAns(toV.ptr[2], toV.ptr[i]);
        addAns(toU.ptr[0], toU.ptr[1]);
        addAns(toU.ptr[1], toU.ptr[2]);
        for (int i = 3; i < szU; i++)
            addAns(toU.ptr[2], toU.ptr[i]);
    }
    if (toNon.sz==0) {
        addAns(toV.ptr[min(2, szV - 1)], toU.ptr[min(2, szU - 1)]);
    } 
    else {
        addAns(toV.ptr[min(2, szV - 1)], toNon.ptr[0]);
        addAns(toU.ptr[min(2, szU - 1)], toNon.ptr[0]);
        for (int i = 1; i < toNon.sz; i++)
            addAns(toNon.ptr[0], toNon.ptr[i]);
    }
    printAns();
}
int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i]);
        if (p[i] != -1) p[i]--;
        if (p[i] != -1)
            isFarthest[p[i]]++;
    }
    if (n == 1) {
        if (p[0] != 0) 
            Fail();
        printAns();
    }
    if (n == 2) {
        if (p[0] != 1 || p[1] != 0) 
            Fail();
        addAns(0, 1);
        printAns();
    }
    int V = -1, U = -1, W = -1;
    for (int i = 0; i < n; i++) {
        if (isFarthest[i] == 0) 
            continue;
        if (V == -1)
            V = i;
        else if (U == -1)
            U = i;
        else if (W == -1)
            W = i;
    }
    if (W != -1) 
        Fail();
    if (V == -1) {
        if (n <= 3) 
            Fail();
        for (int i = 1; i < n; i++)
            addAns(0, i);
        printAns();
    }
    if (U == -1)
        solveOne(V);
    else
        solveTwo(V, U);
    return 0;
}












































