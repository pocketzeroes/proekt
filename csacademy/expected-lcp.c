#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAX=(int)1e6+7};
enum{ MAXX = 27};
double ans;
int n;
char s[100000];
int Trie[MAXX][MAX];
int nxt=1,cnt[MAX];

ll func(){
    ll ans=0;
    int i=0,v=0,bck=0;
    int ssize=strlen(s);
    while(i<ssize){
        if(!Trie[s[i]-'a'][v])
            v=Trie[s[i++]-'a'][v]=nxt++;
        else
            v=Trie[s[i++]-'a'][v];
        ans+=cnt[v];
        cnt[v]++;
    }
    return ans;
}
int main(){
    scanf("%d", &n);
    for(int i=1; i<=n; i++){
        scanf("%s", &s);
        ans += func();
    }
    double total = n;
    total = total*(n-1);
    total = total/2.0;
    ans = ans/total;
    printf("%f\n", ans);
    return 0;
}
