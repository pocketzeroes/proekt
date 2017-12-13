#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct pair{
    int    first;
    double second;
}pair;
pair newPair(int a, double b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}

enum{ SIZE = 601};
int  v2[SIZE];
pair v [SIZE];


pair b[SIZE];//int double
int NOW;
double dp[SIZE][SIZE];

void handle(pair*a1, int n1, pair*a2, int n2, pair*res){
    for (int i = (0); i <= (n1); ++i)
        for (int j = (0); j <= (n2); ++j)
            dp[i][j]=0;
    dp[0][0]=1;
    for (int i = 0; i < (n1+n2); ++i)
        res[i]=newPair(a1[0].first,0);
    for (int i = (0); i <= (n1); ++i){
        for (int j = (0); j <= (n2); ++j){
            if(i==n1&&j==n2)
                break;
            int to_id=i+j;
            if(i==n1){
                dp[i][j+1]+=dp[i][j];
                res[to_id].second+=dp[i][j]*a2[j].second;
            }
            else if(j==n2){
                dp[i+1][j]+=dp[i][j];
                res[to_id].second+=dp[i][j]*a1[i].second;
            }
            else{
                dp[i+1][j]+=dp[i][j]*0.5;
                dp[i][j+1]+=dp[i][j]*0.5;
                res[to_id].second+=dp[i][j]*0.5*(a1[i].second+a2[j].second);
            }
        }
    }
}
void merge_sort(pair*a, int from, int to) {
    if (to <= from)
        return;
    int mid = (from + to) / 2;
    merge_sort(a,from, mid);
    merge_sort(a,mid + 1, to);
    int le = from, ri = mid + 1;
    for (int i = from; i <= to; ++i) {
        if (ri > to || (le <= mid && a[le].first<a[ri].first)) {
            b[i] = a[le++];
        }
        else if(le > mid || (ri <= to && a[le].first>a[ri].first)){
            b[i] = a[ri++];
        }
        else if(a[le].first!=NOW){
            b[i] = a[le++];
        }
        else{
            int nxt_le=le;
            while(nxt_le<=mid&&a[le].first==a[nxt_le].first)nxt_le++;
            int nxt_ri=ri;
            while(nxt_ri<=to&&a[ri].first==a[nxt_ri].first)nxt_ri++;
            handle(a+le,nxt_le-le,a+ri,nxt_ri-ri,b+i);
            i+=nxt_le-le+nxt_ri-ri-1;
            le=nxt_le;
            ri=nxt_ri;
        }
    }
    for (int i = from; i <= to; ++i) {
        a[i] = b[i];
    }
}
int main(){
    int N;
    scanf("%d", &N);
    for (int i = 0; i < (N); ++i){
        scanf("%d", &v2[i]);
    }
    for (int i = 0; i < (N); ++i){
        for (int j = 0; j < (N); ++j){
            v[j] = newPair(v2[j],0);
        }
        v[i].second=1;
        NOW=v[i].first;
        merge_sort(v,0,N-1);
        double an=1;
        for (int j = 0; j < (N); ++j)
            an+=v[j].second*j;
        printf("%lf\n", an);
    }
    return 0;
}
