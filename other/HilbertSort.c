#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
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

char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
char*concatii(int a, int b){
  char*ptr=NULL;
  asprintf(&ptr, "%d %d", a, b);
  return ptr;
}

typedef struct{
    int x, y;
    char*label;
    char*key;
}Location;

Location newLocation(int x, int y, char*l, char*k){
    return(Location){x, y, l, k};
}
int cmpL(const void*pa, const void*pb){
    Location*tva=(Location*)pa;
    Location*loc=(Location*)pb;
    return strcmp(tva->key, loc->key);
}
char*makekey(double x, double y, double s, int level){
    char*key = strdup("");
    if(level>0){
        --level;
        double s2 = s/2.0;
        if     ( x<=s2 && y<=s2 ){key = concats("a", makekey(y, x, s2,       level));}
        else if( x<=s2 && y> s2 ){key = concats("b", makekey(x, y-s2, s2,    level));}
        else if( x> s2 && y> s2 ){key = concats("c", makekey(x-s2, y-s2, s2, level));}
        else if( x> s2 && y<=s2 ){key = concats("d", makekey(s2-y, s-x, s2,  level));}
    }
    return key;
}
int main(){
    int    n = in_nextInt();
    double s = in_nextDouble();
    Location locs[n];
    for(int i=0; i<n; i++){
        int x = in_nextInt();
        int y = in_nextInt();
        char*lab = concatii(x, y);
        locs[i] = newLocation(x, y, lab, makekey((double)x, (double)y, s, 30));
    }
    qsort(locs, n, sizeof(Location), cmpL);
    for(int z=0; z<n; z++){
        puts(locs[z].label);
    }
    return 0;
}
