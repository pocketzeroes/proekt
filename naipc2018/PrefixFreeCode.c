#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int cmpstr(const void*p1, const void*p2){
  return strcmp(*(char* const*) p1, *(char* const*) p2);
}
typedef long long ll;
#define mod 1000000007LL
enum{maxn =(int) 1e6 +1000};

typedef struct{
    bool judge;
    int  next[26];
    int  index;
}Node;
Node node[maxn];
int n,m,root,tot;
ll ans[maxn],c[maxn],sum;

int ID(){
    node[tot].judge = false;
    memset(node[tot].next,-1,sizeof (node[tot].next));
    node[tot].index = 0;
    return tot++;
}
int lowbit(int x){
    return x&(-x);
}
ll getSum(int x){
    ll Sum = 0;
    for(int i = x; i; i-= lowbit(i)){
        Sum += c[i];
    }
    return Sum;
}
void addSum(int x,int val){
    for(int i = x + 1; i <= n; i += lowbit(i))
        c[i]+=val;
}
void BuildTree(int r, char*s,int id){
    int len = strlen(s);
    for(int i = 0; i < len; i++){
        int num = s[i] - 'a';
        if(node[r].next[num] == -1){
            node[r].next[num] = ID();
        }
        r = node[r].next[num];
    }
    node[r].judge = true;
    node[r].index = id;
}
void init(){
    tot = sum = 0;
    ans[m] = 1;
    ll res = (n - m + 1) % mod;
    for(int j = m - 1; j >= 1; j--){
        ans[j] = (ans[j+1] * res) % mod;
        res = (res + 1) % mod;
    }
    memset(c,0,sizeof c);
    for(int i = 1 ; i <=n ; i++){
        addSum(i,1);
    }
}
void searchTree(int r, char*s){
    int len = strlen(s);
    int pos = 1;
    for(int  i = 0 ; i < len; i++){
        int num = s[i] - 'a';
        r = node[r].next[num];
        if(node[r].judge){
            int k = node[r].index;
            sum += (ans[pos] * getSum(k)) % mod;
            addSum(k,-1);
            pos++;
            r = root;
        }
    }
}
char buff[500000];
int main(){
    scanf("%d %d", &n, &m);
    char*v[n];
    init();
    root = ID();
    for(int i=0; i<n; i++){
        scanf("%s", &buff);
        v[i] = strdup(buff);
    }
    qsort(v, n, sizeof(char*), cmpstr);
    for(int j=0; j<n; j++){
        BuildTree(root, v[j], j+1);
    }
    scanf("%s", &buff);
    searchTree(root, buff);
    printf("%lld\n", (sum+1)%mod);
    return 0;
}
