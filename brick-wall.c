#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>


typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
int cmp (const void * pa, const void * pb)
{
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    int diff = a->first - b->first;
    if(diff!=0)return diff;
    return a->second - b->second;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

pair*pushback(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}

  int min(int a,int b){return a<b?a:b;}
  int max(int a,int b){return a>b?a:b;}

enum{ INF = (int)1E9};


int leastBricks(int**wall, int wallSz, int*wallSizes){
    int n = wallSz;
    pair*es=NULL;int esSz=0;
    int xr = 0;
    for(int i=0;i<n;i++){
        int m = wallSizes[i], sum = 0;
        for(int j=0;j<m;j++) {
            int l = sum, r = sum + wall[i][j];
            es=pushback(es,&esSz,newPair(l, 1));
            es=pushback(es,&esSz,newPair(r, 0));
            sum += wall[i][j];
        }
        xr = max(xr, sum);
    }
    qsort(es, esSz, sizeof(pair), cmp);
    int ans = INF, cnt = 0, E = esSz;
    for(int i=0;i<E;i++){
        int x = es[i].first, j = i;
        if (x == xr) ans = min(ans, cnt);
        while (j < E && es[j].first == x && es[j].second == 0) {
            j++;
            cnt--;
        }
        if (x != 0 && x != xr) ans = min(ans, cnt);
        while (j < E && es[j].first == x && es[j].second == 1) {
            j++;
            cnt++;
        }
        if (x == 0) ans = min(ans, cnt);
        i = j - 1;
    }
    return ans;
}

#if 0
int main(){
    int**vec=malloc(6*sizeof(int*));
    vec[0]=malloc(4*sizeof(int));
    vec[1]=malloc(3*sizeof(int));
    vec[2]=malloc(3*sizeof(int));
    vec[3]=malloc(2*sizeof(int));
    vec[4]=malloc(3*sizeof(int));
    vec[5]=malloc(4*sizeof(int));
    
    vec[0][0]=1;
    vec[0][1]=2;
    vec[0][2]=2;
    vec[0][3]=1;

    vec[1][0]=3;
    vec[1][1]=1;
    vec[1][2]=2;

    vec[2][0]=1;
    vec[2][1]=3;
    vec[2][2]=2;

    vec[3][0]=2;
    vec[3][1]=4;

    vec[4][0]=3;
    vec[4][1]=1;
    vec[4][2]=2;

    vec[5][0]=1;
    vec[5][1]=3;
    vec[5][2]=1;
    vec[5][3]=1;
    
    
    int sizes[]={4,3,3,2,3,4};
    leastBricks(vec,6,sizes);
}
#endif

















