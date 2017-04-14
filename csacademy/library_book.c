#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
typedef struct pair{
    int first;
    int second;
}pair;
pair newPair(int a, int b){
    pair rez;
    rez.first =a;
    rez.second=b;
    return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushback(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
int cmp (const void * pa, const void * pb)
{
    pair*a=(pair*)pa;
    pair*b=(pair*)pb;
    int diff = a->first - b->first;
    if(diff!=0)return diff;
    return a->second - b->second;
}
void reverse(pair*arr, int start, int end)
{
    pair ttt;
    while(start < end)
    {
        memcpy( &ttt       , &arr[start], sizeof(pair));
        memcpy( &arr[start], &arr[end  ], sizeof(pair));
        memcpy( &arr[end]  , &ttt       , sizeof(pair));
        start++;
        end--;
    }   
}  
const int INF = 1e9;
pair*p  ;int pSz  ;
pair*s  ;int sSz  ;
pair*tmp;int tmpSz;
int n, m;
int dp[3100][3100];
int main() {
    p  =NULL; pSz  =0;
    s  =NULL; sSz  =0;
    tmp=NULL; tmpSz=0;
    memset(dp,0,sizeof(dp));
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		p=pushback(p,&pSz,newPair(a, b));
	}
	qsort(p, pSz, sizeof(pair), cmp);
	for (int i = 0; i < m; ++i){
		int a, b;
		scanf("%d%d", &a, &b);
		tmp=pushback(tmp,&tmpSz,newPair(a, b));
    }
	qsort(tmp, tmpSz, sizeof(pair), cmp);
	int mx = 0;
    reverse(tmp,0,tmpSz-1);
	for (int i = 0; i < m; ++i){
		if (tmp[i].second > mx){
			mx = tmp[i].second;
			s=pushback(s,&sSz,tmp[i]);
		}
	}
	reverse(s, 0, sSz-1);
	m = sSz;
	for (int i = 0; i <= n; ++i){
		if (i == 0)
			dp[i][0] = 0;
		else
			dp[i][0] = max(dp[i - 1][0], p[i - 1].first) + p[i - 1].second;
		int go = INF;
		for (int j = 1; j <= m; ++j) {
			dp[i][j] = INF;
			if (i > 0)
				dp[i][j] = min(dp[i][j], max(dp[i - 1][j], p[i - 1].first) + p[i - 1].second);
			dp[i][j] = min(dp[i][j], max(dp[i][j - 1], s[j - 1].first) + s[j - 1].second);
			dp[i][j] = min(dp[i][j], max(go, s[j - 1].first + s[j - 1].second));
			go = min(max(go, s[j - 1].first + s[j - 1].second), max(dp[i][j - 1], s[j - 1].first) + s[j - 1].second);
		}
	}
    printf("%d\n", dp[n][m]);
	return 0;
}































































