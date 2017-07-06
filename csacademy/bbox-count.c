#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
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
int cmpP(const void*pa, const void*pb)
{
  pair*a=(pair*)pa;
  pair*b=(pair*)pb;
  int diff;
  diff = a->first  - b->first;  if(diff!=0) return diff;
  return a->second - b->second;
}


#define ran 2501
#define x first
#define y second
int N;
pair a[ran];
int bit[ran];
bool f[ran];
pair y[ran];
int ly;


int lowbit(int x){
    return x&-x;
}
int query(int x){
    int res = 0;
    while(x){
        res += bit[x] ;
        x -= lowbit(x);
    }
    return res;
}
void add(int x){
    if(f[x])return;
    f[x] = true;
    while(x < ran){
        bit[x] ++;
        x += lowbit(x);
    }
}
int main(){
    scanf("%d",&N);
    for(int i=0; i<N; i++)
        scanf("%d%d",&a[i].x,&a[i].y);
    qsort(a, N, sizeof(pair), cmpP);
    long long res = 0;
    for(int S=0,T; S<N; S=T){
        for(T=S; T<N && a[T].x == a[S].x; T++);
        memset(bit,0,sizeof(bit));
        memset(f,0,sizeof(f));
        for(int i=S; i<T; i++)
            add(a[i].y);
        for(int S2=T, T2; S2 < N; S2=T2){
            for(T2 = S2; T2 < N && a[T2].x == a[S2].x; T2++);
            for(int i=S2; i<T2; i++)
                add(a[i].y);
            ly=0;
            for(int i=S; i<T; i++)
                y[ly++] = newPair(a[i].y, 1);
            for(int i=S2; i<T2; i++)
                y[ly++] = newPair(a[i].y, -1);
            qsort(y, ly, sizeof(pair), cmpP);
            int pnt = 0;
            int cntA = 0, cntB = 0;
            int prev = 0;
            for(int i=0; i<ly; i++){
                while(pnt < ly && (y[pnt].first <= y[i].first || cntA == 0 || cntB == 0)){
                    if(y[pnt].second == -1)
                        cntA++;
                    else
                        cntB++;
                    pnt ++;
                }
                if(i==0 || y[i].first != y[i-1].first){
                    if(!(cntA == 0 || cntB == 0))
                        res += (query(y[i].first) - query(prev)) * (query(ran-1) - query(y[pnt-1].first-1));
                    prev = y[i].first;
                }
                else
                    res --;
                if(y[i].second == -1)
                    cntA--;
                else
                    cntB --;
            }
        }
    }
    printf("%lld\n", res);
    return 0;
}

















































