#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
typedef struct{
  double first;
  double second;
}pair;
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
int main(){
    int n;
    double w, u, v, t1, t2;
    scanf("%d%lf%lf%lf%lf%lf", &n, &w, &u, &v, &t1, &t2);
    char dir;
    int num;
    double length, pos;
    vecp ships=newVecP();
    for(int i=0; i<n; ++i){getchar();
        scanf("%c %d", &dir, &num);
        double time = w/v*i;
        while(num--){
            scanf("%lf %lf", &length, &pos);
            double endPos;
            if(dir == 'E'){
                endPos = pos-length;
                pos *= -1;
                endPos *= -1;
            }
            else
                endPos = pos+length;
            pos -= time*u;
            endPos -= time*u;
            ships.ptr = pushbackP(ships.ptr, &ships.sz, (pair){pos/u-w/v, endPos/u});
        }
    }
    qsort(ships.ptr, ships.sz, sizeof(pair), cmpP);
    double maxSoFar = t1, maxTime = 0;
    for(int z=0;z<ships.sz;z++){pair p = ships.ptr[z];
        if(p.first > maxSoFar)
            maxTime = fmax(maxTime, fmin(p.first,t2) - maxSoFar);
        maxSoFar = fmax(maxSoFar, p.second);
        if(maxSoFar >= t2)
            break;
    }
    printf("%.8lf\n", fmax(maxTime, t2-maxSoFar) );
    return 0;
}
