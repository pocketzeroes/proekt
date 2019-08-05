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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ NORMALNO = 0};
enum{ OBRNUTO  = 1};
int dostupan[2][10000];
vec susjedi [2][10000];

typedef struct{
   bool jelvelik;
   int  vrijednost;
}MojBroj;
MojBroj newMojBroj(int x){
   MojBroj rez;
   rez.jelvelik   = false;
   rez.vrijednost = x;
   return rez;
}
MojBroj opAdd(MojBroj A, MojBroj B){
   MojBroj C=newMojBroj(A.vrijednost+B.vrijednost);
   C.jelvelik = A.jelvelik|B.jelvelik;
   if(C.vrijednost >= 1000000000){
      C.jelvelik = true;
      C.vrijednost -= 1000000000;
   }
   return C;
}
void dfs(int G, int i){
   if(dostupan[G][i])
      return;
   dostupan[G][i] = 1;
   for(int z=0;z<susjedi[G][i].sz;z++){int it=susjedi[G][i].ptr[z];
      dfs( G, it);
   }
}
enum Boja{Bijela, Siva, Crna}boja[10000];
MojBroj memo[10000];

MojBroj rekurzija( int i ){
   if( boja[i] == Crna )
      return memo[i];
   if( boja[i] == Siva ){
      puts("inf");
      exit(0);
   }
   boja[i] = Siva;
   memo[i] = newMojBroj(0);
   if( i == 1 )
      memo[i] = newMojBroj(1);
   for(int z=0;z<susjedi[0][i].sz;z++){int it=susjedi[0][i].ptr[z];
      if(dostupan[NORMALNO][it]&&
         dostupan[OBRNUTO ][it])
         memo[i] = opAdd(memo[i], rekurzija(it));
   }
   boja[i] = Crna;
   return memo[i];
}
int main(){
   int n, m;
   scanf("%d %d", &n, &m);
   for(int i=0; i<m; ++i){
      int a, b;
      scanf("%d %d", &a, &b);
      --a, --b;
      susjedi[NORMALNO][a].ptr = pushback(susjedi[NORMALNO][a].ptr, &susjedi[NORMALNO][a].sz, b);
      susjedi[OBRNUTO ][b].ptr = pushback(susjedi[OBRNUTO ][b].ptr, &susjedi[OBRNUTO ][b].sz, a);
   }
   dfs(NORMALNO, 0);
   dfs(OBRNUTO , 1);
   MojBroj ret = rekurzija(0);
   if(ret.jelvelik)
      printf("%09d\n", ret.vrijednost);
   else
      printf("%d\n", ret.vrijednost);
   return 0;
}
