#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
double in_nextDouble(){
  double xx;
  scanf("%lf", &xx);
  return xx;
}
//////////////////////
typedef struct Key{
    int    row, column;
    double probability;
}Key;
Key newKey(int r, int c, double p){
    return(Key){r,c,p};
}
int cmpKPROB(const void*pa, const void*pb){// by PROB
    Key*one  =(Key*)pa;
    Key*other=(Key*)pb;
    if(one->probability > other->probability)
        return -1;
    else if (one->probability < other->probability)
        return 1;
    else
        return 0;
}
int cmpKLEX(const void*pa, const void*pb){// by LEX
    Key*one  =(Key*)pa;
    Key*other=(Key*)pb;
    if (one->row < other->row || (one->row == other->row && one->column < other->column))
        return -1;
    else if (one->row == other->row && one->column == other->column)
        return 0;
    else
        return 1;
}
#define pb(zpv, zvv) zpv.ptr = pushbackK(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
Key*pushbackK(Key*array, int *size, Key value){
  Key*output = resizeArray(array, Key, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	Key*ptr;
	int sz;
}veck;
veck newVecK(){
	veck rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////////////////////////////
int N, M;
veck key_list; // of Key
veck solution; // of Key



int*p;
int*r;
void UFDS(int N){
    p = calloc(N, sizeof(int));
    r = calloc(N, sizeof(int));
    for(int j=0; j<N; j++){
        p[j] = j;
        r[j] = 0;
    }
}
int find(int i){
    if (p[i]==i)
        return i;
    else
        return find(p[i]);
}
void unionn(int i, int j){
    int x=find(i), 
        y=find(j);
    if(x!=y){
        if(r[x]>r[y])
            p[y]=x;
        else{
            p[x]=y;
            if (r[x]==r[y])
                r[y]++;
        }
    }
}

void kruskal(){
    qsort(key_list.ptr, key_list.sz, sizeof(Key), cmpKPROB);
    UFDS(N+M);
    solution = newVecK();
    for(int z=0;z<key_list.sz;z++){Key front = key_list.ptr[z];
        if(find(front.row)!=find(N+front.column)){
            unionn(front.row,N+front.column);
            pb(solution, front);
        }
    }
}
int main(){
    N = in_nextInt();
    M = in_nextInt();
    double*matrix[N];
    for(int i=0; i<N; i++){
        matrix[i] = calloc(M, sizeof(double));
        for(int j=0; j<M; j++){
            matrix[i][j] = in_nextDouble();
        }
    }
    key_list = newVecK();//of Key
    for(int row=0; row < N ; row++){
        int aux = in_nextInt();
        for(int j = 1; j <= aux; j++){
            int col = in_nextInt();
            pb(key_list, newKey(row, col , matrix[row][col]));
        }
    }
    kruskal();
    qsort(solution.ptr, solution.sz, sizeof(Key), cmpKLEX);
    for(int z=0;z<solution.sz;z++){Key k = solution.ptr[z];
        printf("%d %d\n", k.row, k.column);
    }
    return 0;
}
