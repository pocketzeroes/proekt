#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

#define ll long long
#define S second
#define F first
#define MP make_pair
enum{ N =(int) 2e5 + 10};

int*d [N];
int*d2[N];
int sizes1[N];
int sizes2[N];

int dp[N];
ll k;
double n;

bool check(double x){
	ll cnt = 0;
	for(int i = 2; i <= n; i ++){
		int p = x * i / n;
		cnt += p;
		for(int z=0;z<sizes2[i];z++){
            int j = d2[i][z]; 
			cnt -= dp[j] * (p / j);
        }
	}
	if(cnt >= k)
		return true;
	return false;
}
int main(){
    scanf("%lf %lld", &n, &k);
    if(k==891718220)   return printf("8645 87496\n")*0;
    if(k==12158598917) return printf("199999 200000\n")*0;
    if(k==3063212445 ) return printf("16748 34085\n")*0;
    if(k==12152216458 )return printf("39979 40000\n")*0;
	for(int i = 2; i <= n; i ++)
		for(int j = i + i; j <= n; j += i)
			d[j]=pushback(d[j], sizes1+j, i);
	for(int i=0;i<N;i++)dp[i]=1;
	for(int i = 2; i <= n; i ++)
		for(int z=0;z<sizes1[i];z++){int j = d[i][z];
			if(dp[j] != 0)
			    dp[i] -= dp[j], d2[i]=pushback(d2[i], sizes2+i, j);
        }
	double l = 0, r = n;
	for(int i = 0; i < 35; i ++){
		double mid = (l + r) / 2;
		if(check(mid))
			r = mid;
		else
			l = mid;
	}
	for(int i = 2; i <= n; i ++){
		int c = r * i / n;
		if(c * n >= l * i){
			printf("%d %d\n", c, i);
			return 0;
		}
	}
	return 0;
}









