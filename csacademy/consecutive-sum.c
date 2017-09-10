#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int n;
ll P[100001];

int main(){
    scanf("%d", &n);
    P[0]=0;
    for (int i=1;i<=n;i++)
        P[i]=P[i-1]+i;
    for (int i=1;i<=n;i++)
      if (P[i]>=0LL+n){
        int p=P[i]-n;
        int l=0,r=i-2;
        while (l<=r){
            int mid=(l+r)/2;
            if (P[mid]==p){
                printf("%d %d",mid+1,i);
                return 0;
            }
            if (P[mid]<p)
                l=mid+1;
            else
                r=mid-1;
        }
      }
    printf("-1");
    return 0;
}
