#include <stdio.h>
#define N 100000
int a[N+1];
int b[N+1];
int minim(int a,int b){
    if (a==-1) return b;
    if (b==-1) return a;
    return (a<b) ? a : b;
}
int main(){
    int n,i;
    scanf ("%d",&n);
    for(i=1;i<=n;i++)
        scanf ("%d%d",&a[i],&b[i]);
    int min=0;
    int prev=b[1];
    for(i=2;i<=n;i++){
        if (a[i]==prev) 
            prev=b[i];
        else if (b[i]==prev){
            min++;
            prev=a[i];
        }
        else {
            min=-1;
            break;
        }
    }
    int cnt=1;
    prev=a[1];
    for(i=2;i<=n;i++){
        if (a[i]==prev) prev=b[i];
        else if (b[i]==prev){
            cnt++;
            prev=a[i];
        }
        else {
            cnt=-1;
            break;
        }
    }
    printf ("%d",minim(min,cnt));
    return 0;
}
