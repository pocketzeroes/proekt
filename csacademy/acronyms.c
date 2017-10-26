#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ N=(int)1e5 + 5};
char arr[N * 10];
char*s[N];
int freq[26];

int main(){
	int n;
	scanf("%d", &n);
	for(int i=0;i < n;i++){
		scanf(" %s",arr);
		s[i]=strdup(arr);
		freq[arr[0] - 'a']++;
	}
	int ans=0;
	for(int i=0;i < n;i++){
		freq[s[i][0] - 'a']--;
		bool f=1;
		for(int j=0;s[i][j];j++){
			int d=s[i][j] - 'a';
			if(freq[d] <= 0) f=0;
			freq[d]--;
		}
		for(int j=0;s[i][j];j++){
			int d=s[i][j] - 'a';
			freq[d]++;
		}
		if(f) ans++;
		freq[s[i][0] - 'a']++;
	}
	printf("%d\n", ans);
}
