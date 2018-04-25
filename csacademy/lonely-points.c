#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>

int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int main(){
    int n;
    scanf("%d", &n);
    int a[n];
    for(int i=0;i<n;i++)
        scanf("%d", &a[i]);
    int ans = 0x7f7f7f7f;
    {   int df[n-2]; 
        int mx = 0;
        int mxind;
        for(int i = 1; i < n-1; ++i){
            df[i-1] = a[i+1] - a[i];
            if(df[i-1] > mx){
                mx = df[i-1];
                mxind = i-1;
            }
        }
        mx = 0;
        for(int i = 1; i < n-1; ++i){
            if(i-1 == mxind){
                mx = max(mx, (df[i-1]+1)/2);
                continue;
            }
            if(df[i-1] > mx)
                mx = df[i-1];
        }
        ans = min(ans,mx);
    }
    {   int df[n-2]; 
        int mx = 0;
        int mxind;
        for(int i = 0; i < n-2; ++i){
            df[i] = a[i+1] - a[i];
            if(df[i] > mx){
                mx = df[i];
                mxind = i;
            }
        }
        mx = 0;
        for(int i = 0; i < n-2; ++i){
            if(i == mxind){
                mx = max(mx, (df[i]+1)/2);
                continue;
            }
            if(df[i] > mx)
                mx = df[i];
        }
        ans = min(ans,mx);
    }
    printf("%d\n", ans);
    return 0;
}

