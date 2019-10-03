#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int in_nextInt(){
  int xx;
  scanf("%d", &xx);
  return xx;
}
typedef struct Emp{
    int ID, sal, hte, boss, nsub;
}Emp;
int cmpE(const void*pa, const void*pb){
    Emp*t=(Emp*)pa;
    Emp*o=(Emp*)pb;
    return t->sal - o->sal;
}
int main(){
    int nemp = in_nextInt();
    int nq   = in_nextInt();
    int*IDtoIndex=calloc(1000000, sizeof(int));
    Emp emp[nemp]; clr(emp);
    for(int i = 0; i < nemp; ++i){
        emp[i].ID   = in_nextInt();
        emp[i].sal  = in_nextInt();
        emp[i].hte  = in_nextInt();
        emp[i].boss = -1;
    }
    qsort(emp, nemp, sizeof(Emp), cmpE);
    for(int i = 0; i < nemp; ++i)
        IDtoIndex[emp[i].ID] = i;
    for(int i = nemp-2; i >= 0; --i){
        int b = i+1;
        while(emp[i].hte > emp[b].hte)
            b = emp[b].boss;
        emp[i].boss = b;
    }
    for(int i = 0; i < nemp-1; ++i)
        emp[emp[i].boss].nsub += (1 + emp[i].nsub);
    for(int i = 0; i < nq; ++i){
        int q=0;
        q = in_nextInt();
        int ix = IDtoIndex[q];
        int bix = emp[ix].boss;
        if (bix == -1)
            putchar('0');
        else
            printf("%d", emp[bix].ID);
        printf(" %d", emp[ix].nsub);
        puts("");
    }
    free(IDtoIndex);
    return 0;
}
