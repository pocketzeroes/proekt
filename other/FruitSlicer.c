#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

typedef struct{
  int    first;
  double second;
}pid;
typedef struct{
  double first;
  bool   second;
}pdb;

int compP(pid a, pid b){
    if(a.first !=b.first )return(a.first <b.first )?-1:1;
    if(a.second!=b.second)return(a.second<b.second)?-1:1;
    return 0;
}
pid maxP(pid a,pid b){return compP(a,b)>0?a:b;}

int cmpP(const void*pa, const void*pb){
  pdb*a = (pdb*)pa;
  pdb*b = (pdb*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}
/////////////////////
int n;
double x[100];
double y[100];

pid test(double rot){
    int result = 0;
    pdb range[2*n];
    for(int i=0, z=0; i<n; ++i){
        range[z++] = (pdb){x[i] * sin(rot) - y[i] * cos(rot) - 1.000001, false};
        range[z++] = (pdb){x[i] * sin(rot) - y[i] * cos(rot) + 1.000001, true };
    }
    qsort(range, 2*n, sizeof(pdb), cmpP);
    int current=0;
    for(int z=0;z<2*n;z++){pdb i = range[z];
        if(!i.second)
            current++;
        else
            current--;
        result = max(result, current);
    }
    return(pid){result, rot};
}
int main(){
    scanf("%d", &n);
    for(int i=0; i<n; ++i)
        scanf("%lf%lf", &x[i], &y[i]);
    pid best = (pid){0, 0.};
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            best = maxP(best, test(atan2(y[j] - y[i], x[j] - x[i])));
    for (double rot = 0; rot < M_PI; rot += 1e-2)
        best = maxP(best, test(rot));
    for (double delta=1e-2; delta>=1e-8; delta*=.5){
        best = maxP(best, test(best.second + delta));
        best = maxP(best, test(best.second - delta));
    }
    printf("%d\n", best.first);
    return 0;
}
