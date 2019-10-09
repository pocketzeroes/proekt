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
char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
}
char*getln(){
  gets(buff);
  return strdup(buff);
}

#define pb(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
unsigned cntwords(char*str){
    enum{ OUT = 0, IN  = 1};
    int state = OUT;
    unsigned wc = 0;
    while(*str){
        if(*str == ' ' || *str == '\n' || *str == '\t')
            state = OUT;
        else if(state == OUT){
            state = IN;
            ++wc;
        }
        ++str;
    }
    return wc;
}
/////////////////////////
int main(){
    char*kk=getln();
    int k = cntwords(kk);
    int n = in_nextInt();
    char*w[n];
    for(int i=0; i<n; i++)
        w[i] = getstr();
    int s[n]; clr(s);
    int p = 0;
    vecs a = newVecS();
    vecs b = newVecS();
    for(int h=0; h<n; h++){
        int c = 0;
        while(c < k){
            if(s[p] == 0)
                c++;
            if(c == k){
                s[p] = 1;
                if(h%2 == 0)
                    pb(a, w[p]);
                else
                    pb(b, w[p]);
            }
            p++;
            if(p == n)
               p =  0;
        }
    }
    printf("%d\n", a.sz);
    for(int z=0; z<a.sz; z++){char*x = a.ptr[z];
        puts(x);
    }
    printf("%d\n", b.sz);
    for(int z=0; z<b.sz; z++){char*x = b.ptr[z];
        puts(x);
    }
    return 0;
}
