#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int cmp(const void*a, const void*b){ return ( *(int*)a - *(int*)b );}
int unique(int*a, int len){
	int i, j;
	for (i = j = 0; i < len; i++)
		if (a[i] != a[j])
      a[++j] = a[i];
	return j + 1;
}

enum{ M = 500001};
int N;
int par[M+1],
    sz [M+1];

int cp(int n){
    return par[n] == n ? n : (par[n] = cp(par[n]));
}
int main(){
    for (int i=1;i<=M;i++)
        par[i] = i, sz[i] = 1;
    scanf("%d", &N);
    int ans = 0;
    for(int i=1;i<=N;i++){
        int n;
        scanf("%d", &n);
        int arr[n]; memset(arr, 0, sizeof(arr));
        int arrsz=n;
        for(int j=0; j<n; j++)
            scanf("%d", &arr[j]), arr[j] = cp(arr[j]+1);
        qsort(arr, n, sizeof(int), cmp);
        arrsz = unique(arr, n);
        int sum = 0;
        for(int z=0;z<arrsz;z++){int t = arr[z];
            sum += sz[t];
        }
        if(sum != n)
            continue;
        ans++;
        for(int j=1;j<arrsz;j++){
            int a = arr[0], 
                b = arr[j];
            par[b] = a;
            sz[a] += sz[b];
            sz[b] = 0;
        }
    }
    printf("%d\n", ans);
    return 0;
}
