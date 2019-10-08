#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxn = 100000};
enum{ oo = (int) 1e9+10};
int n;
int v[maxn+1],
    d[maxn+1];
int p[2][7][maxn+1];
int dayFactor[7] = {0,1,2,3,2,1,0};
int l[2][7][maxn*5],r[2][7][maxn*5];

typedef struct node{
    int maxi,
        mini,
        maxDiff;
}node;
node it[2][7][maxn*5];

void initArray(){
    for (int i=0; i<7; i++){
        int currentDay  = i;
        int startingDay = i;
        for (int j = 1; j <= n; j++) {
            p[0][startingDay][j] = v[j] + d[j] * dayFactor[currentDay];
            currentDay = (currentDay + 1) % 7;
        }
    }
    for (int i=0; i<7; i++){
        int currentDay = i;
        int startingDay = i;
        for (int j=n; j>=1; j--){
            p[1][startingDay][n-j+1] = v[j] + d[j]*dayFactor[currentDay];
            currentDay = (currentDay+1)%7;
        }
    }
}
void merge(node*res, node*left, node*right){
    res->maxi    = fmax(left->maxi,    right->maxi);
    res->mini    = fmin(left->mini,    right->mini);
    res->maxDiff = fmax(left->maxDiff, right->maxDiff);
    res->maxDiff = fmax(res ->maxDiff, right->maxi - left->mini);
}
void initIT(int id1, int id2, int i, int x, int y){
    l[id1][id2][i] = x;
    r[id1][id2][i] = y;
    if (x==y){
        it[id1][id2][i].maxi = p[id1][id2][x];
        it[id1][id2][i].mini = p[id1][id2][x];
        it[id1][id2][i].maxDiff = 0;
    }
    else{
        int m = (x+y)/2;
        initIT(id1,id2,i<<1,x,m);
        initIT(id1,id2,(i<<1)+1,m+1,y);
        merge(&it[id1][id2][i], &it[id1][id2][i<<1], &it[id1][id2][(i<<1)+1]);
    }
}
node getIT (int id1, int id2, int i, int x, int y){
    if (y<l[id1][id2][i] || x>r[id1][id2][i])
        return(node){-oo,oo,0};
    if (x<=l[id1][id2][i] && r[id1][id2][i]<=y)
        return it[id1][id2][i];
    node resLeft  = getIT(id1,id2,i<<1,x,y);
    node resRight = getIT(id1,id2,(i<<1)+1,x,y);
    node res;
    merge(&res, &resLeft, &resRight);
    return res;
}
int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++)
        scanf("%d %d", &v[i], &d[i]);
    initArray();
    for(int i=0; i<2; i++)
        for(int j = 0; j < 7; j++)
            initIT(i, j, 1, 1, n);
    int q;
    scanf("%d", &q);
    for(int i=1; i<=q; i++){
        int s,t;
        scanf("%d %d", &s, &t);
        if(s<=t){
            int startDayFrom1 = (14-(s-1)+7*maxn)%7;
            int version = 0;
            printf("%d\n", getIT(version,startDayFrom1,1,s,t).maxDiff);
        }
        else{
            int version = 1;
            int startDayFromN = (14-(n-s)+7*maxn)%7;
            printf("%d\n", getIT(version,startDayFromN,1,n-s+1,n-t+1).maxDiff );
        }
    }
    return 0;
}
