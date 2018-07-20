#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}

enum{ N = 100005};
typedef long long ll;
int n,n1,n2,a[N],b[N];
int ans[N][2],c;
ll sum;

int main(){
    scanf("%d", &n);
    for(int i=1,x; i<=n; i++){
        scanf("%d", &x);
        sum+=x;
        if(x%2==0)
            a[++n1]=x;
        else
            b[++n2]=x;
    }
    if(sum%2){
        puts("-1");
        return 0;
    }
    for(int i=1; i<=n1; i+=2){
        if(i==n1){
            ans[++c][0]=a[i];
            ans[  c][1]=a[i]/2;
            break;
        }
        if(a[i]==a[i+1])
            continue;
        if(a[i]>a[i+1])
            swap(a, i, i+1);
        ans[++c][0]=a[i+1];
        ans[c  ][1]=a[i];
        ans[++c][0]=(a[i+1]-a[i]);
        ans[c  ][1]=(a[i+1]-a[i])/2;
    }
    for(int i=1; i<=n2; i+=2){
        if(b[i]==b[i+1])
            continue;
        if(b[i]>b[i+1])
            swap(b, i, i+1);
        ans[++c][0] = b[i+1];
        ans[c  ][1] = b[i];
        ans[++c][0] = (b[i+1]-b[i]);
        ans[c  ][1] = (b[i+1]-b[i])/2;
    }
    printf("%d\n", c);
    for(int i=1; i<=c; i++)
        printf("%d %d\n", ans[i][0], ans[i][1]);
    return 0;
}
