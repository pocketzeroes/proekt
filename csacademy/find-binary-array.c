#include<stdio.h>
int a[100005];

int in(){
    int rv;
    scanf("%d", &rv);
    return rv;
}
int main(){
    int n = in(), i,j,x,y,z=0,l[100005],r[100005];
    for(i=0; i<(n); ++i)
        l[i]=in();
    for(i=0; i<(n); ++i)
        r[i]=in();
    if(!l[1])
        a[0]=1;
    if(!r[n-2])
        a[n-1]=1;
    for(i=1;i<n;i++){
        if(z!=l[i]){
            z++;
            a[i-1]=0;
        }
        else{
            a[i-1]=1;
        }
    }
    for(i=0; i<(n); ++i)
        printf("%d", a[i]);
    puts("");
    return 0;
}
