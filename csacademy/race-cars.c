#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ ran = 101101};
typedef struct{
    int id;
    int dist, spd;
}Car;
Car car[ran];
int n, x, y;
int ans[ran];

int cmp(const void*pa, const void*pb){ 
    Car*aa=(Car*)pa;
    Car*bb=(Car*)pb;
    Car a = *aa;
    Car b = *bb;
    return(1LL*a.dist*b.spd < 1LL*b.dist*a.spd ||
           1LL*a.dist*b.spd == 1LL*b.dist*a.spd && a.id < b.id)?-1:1;
}
void proc(int det){
    qsort(car+1, n, sizeof(Car), cmp);
    for(int i=1;i<=n;i++)
        ans[car[i].id] = min(ans[car[i].id], i);
    for(int i=1;i<=n;i++) {
        Car mock = car[i];
        mock.spd += det;
        int l = 1, r = i, res = i;
        while(l<=r) {
            int mi = (l+r)/2;
            if(cmp(&mock, &car[mi])==-1){
                res = mi; 
                r=mi-1;
            } 
            else 
                l=mi+1;
        }
        ans[car[i].id] = min(ans[car[i].id], res);
    }
}
int main(){
    scanf("%d %d %d", &n, &x, &y);
    for(int i=1; i<=n; i++){
        scanf("%d %d", &car[i].dist, &car[i].spd);
        car[i].id = i;
        ans[i]    = n;
    }
    proc(x);
    for(int i=1;i<=n;i++) 
        car[i].spd -= y;
    proc(y);
    for(int i=1;i<=n;i++)
        printf("%d\n", ans[i]);
    return 0;
}
