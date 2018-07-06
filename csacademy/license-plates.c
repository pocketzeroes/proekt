#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
typedef long long ll;

char buff[100000];
int main(){
    ll t,i,j,k,n,m,a,b,c,cnt=0,ans=0,cc=0,f=0;
    scanf("%s", &buff);
    k = strlen(buff);
    for(i=0; i<k; i++){
        if(buff[i]=='d'){
            cnt=10;
            b  =9;
            i++;
            while(i<k && buff[i]=='d'){
                cnt=cnt*(b);
                i++;
            }
            if(ans==0)
                ans=cnt;
            else
                ans*=cnt;
        }
        else{
            cnt=26;
            b  =25;
            i++;
            while(i<k && buff[i]=='c'){
                cnt=cnt*(b);
                i++;
            }
            if(ans==0)
                ans=cnt;
            else
                ans*=cnt;
        }
        if(i==k)
            break;
        i--;
    }
    printf("%lld\n", ans);
    return 0;
}
