#include <stdio.h>

#define N 100000

int frecv[N+1];
int cnt[N+1];

int main(){
    int n,i;
    int max=0;
    int min1=N+1,min2=N+1;
    int tot;
    scanf ("%d",&n);
    for(i=1;i<=n;i++){
        int x;
        scanf ("%d",&x);
        frecv[x]++;
        if (min1>x){
            min2=min1;
            min1=x;
        }
        else
        if (min2>x &&x!=min1) min2=x;
    }
    for(i=1;i<=N;i++){
        cnt[frecv[i]]++;
        if (max<frecv[i]) max=frecv[i];
    }
    tot=n;
    if (max>(n+1)/2){
        printf ("-1");
        return 0;
    }
    int prev=0;
    while(max<tot/2+1 &&tot>0){
        printf ("%d ",min1);
        prev=min1;
        tot--;
        cnt[frecv[min1]]--;
        frecv[min1]--;
        cnt[frecv[min1]]++;
        if (cnt[max]==0) max--;
        if (max>=tot/2+1 ||tot==0) break ;
        printf ("%d ",min2);
        prev=min2;
        tot--;
        cnt[frecv[min2]]--;
        frecv[min2]--;
        cnt[frecv[min2]]++;
        if (cnt[max]==0) max--;
        if (frecv[min2]==0) while(frecv[min2]==0 &&min2<=N) min2++;
        if (frecv[min1]==0){
            min1=min2;
            min2++;
            while(frecv[min2]==0 &&min2<=N) min2++;
            if (frecv[min2]!=0 &&min1==prev){
                printf ("%d ",min2);
                cnt[frecv[min2]]--;
                frecv[min2]--;
                cnt[frecv[min2]]++;
                tot--;
                prev=min2;
            }
            while(frecv[min2]==0 &&min2<=N) min2++;
        }
        if (cnt[max]==0) max--;
    }
    for(i=N;i>0;i--)
        if (frecv[i]==max &&i!=prev) min1=i;
    printf ("%d ",min1);
    frecv[min1]--;
    tot--;
    min2=1;
    while(min2<=N &&(frecv[min2]==0 ||min2==min1)) min2++;
    while(tot>0){
        printf ("%d %d ",min2,min1);
        frecv[min1]--;
        frecv[min2]--;
        tot-=2;
        while(min2<=N &&(frecv[min2]==0 ||min2==min1)) min2++;
    }
    return 0;
}




















