#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}

int main(){
    int n;
    scanf("%d", &n);
    int v[n]; memset(v,0,sizeof(v));
    int ans = 1;
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
        if(i > 0 && v[i] > v[i - 1]) 
            ans++;
        if(i > 0) 
            v[i] = max(v[i], v[i - 1]);
    }
    printf("%d\n", ans);
	return 0;
}
