#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
        
#define MAXN 200000
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
///////////////////////////
int n, m, xam, c, now, dist, cur;
double median;
pair arr[MAXN+5];
int comparator(const void*pa, const void*pb){
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    if((double)(a->second+a->first)/2 == (double)(b->second+b->first)/2)
        return(a->first < b->first)?-1:1;
    return((double)(a->second+a->first)/2 < (double)(b->second+b->first)/2)?-1:1;
}

int main(){
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++){
        int x, y;
        scanf("%d %d", &x, &y);
        if(y < x)
            swap(x, y);
        arr[i] = newPair(x, y);
    }
    qsort(arr, m, sizeof(pair), comparator);
    now    = 0;
    cur    = arr[0].first;
    dist   = arr[0].second-arr[0].first;
    median = (double)(arr[0].second+arr[0].first)/2;
    xam    = 1;
    while(now < m){
        if(median  != (double)(arr[now].second + arr[now].first)/2){
            c = 0;
            median = (double)(arr[now].second+arr[now].first)/2;
            dist = arr[now].second-arr[now].first;
            cur = arr[now].first;
        }
        if(cur != arr[now].first)
            c = 0;
        c += 2;
        if(dist == 1){
            xam = max(xam, c); c = 0;
        }
        else if (dist == 2){
            c++;
            xam = max(xam, c); c = 0;
        }
        now++;
        dist -= 2;
        cur++;
    }
    printf("%d\n", xam);
}
