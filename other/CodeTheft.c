#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000001];
char*getln(){
  char*rv = gets(buff);
  if(rv==NULL)return rv;
  return strdup(buff);
}

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
typedef unsigned long long ull;
#define pbu(zpv, zvv) zpv.ptr = pushbackU(zpv.ptr, &zpv.sz, zvv)
ull*pushbackU(ull*array, int *size, ull value){
  ull*output = resizeArray(array, ull, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	ull*ptr;
	int sz;
}vecu;
vecu newVecU(){
	vecu rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
////////////////////////////////////////

const ull X = 123;
enum{ N = 105};
int n, next[1000005];
char*name[N];
char*s;
vec ans;
vecu code[N];//of ull
vecu T;      //of ull

void hash(char*s, int u){
    char*ss = strdup("");
    int l = 0,
        r = strlen(s)-1,
        len = r+1;
    while(s[l] == ' ' && l < len)
        l++;
    while(s[r] == ' ' && r >= 0)
        r--;
    for(int i = l; i <= r; i++){
        ss = concatc(ss, s[i]);
        while(s[i] == ' ' && s[i + 1] == ' ' && i < r)
            i++;
    }
    if(strcmp(ss, "")==0)
        return;
    ull ans = 0;
    for(int i=strlen(ss)-1; i >= 0; i--)
        ans = ans * X + ss[i];
    pbu(code[u], ans);
}
void build(int i){
    code[i].sz=0;
    while((s=getln())!=NULL && strcmp(s, "***END***")!=0)
        hash(s, i);
}
void getnext(){
    int N = T.sz;
    next[0] = next[1] = 0;
    int j = 0;
    for(int i = 2 ; i <= N; i++){
        while(j && T.ptr[i-1] != T.ptr[j])
            j = next[j];
        if(T.ptr[i-1] == T.ptr[j])
            j++;
        next[i] = j;
    }
}
int find(){
    int ans = 0;
    int N = code[n].sz,
        m = T.sz, j = 0;
    for(int i=0; i<N; i++){
        while(j && code[n].ptr[i] != T.ptr[j])
            j = next[j];
        if(code[n].ptr[i] == T.ptr[j])
            j++;
        ans = fmax(ans, j);
        if(j == m)
            return m;
    }
    return ans;
}
int cal(int u){
    int ans = 0;
    int sz1 = code[u].sz;
    for(int i=0; i<sz1; i++){
        T.sz=0;
        for(int j=i; j<sz1; j++)
            pbu(T, code[u].ptr[j]);
        getnext();
        ans = fmax(ans, find());
    }
    return ans;
}
void solve(){
    int Max = 0;
    ans.sz=0;
    for(int i=0; i<n; i++){
        int tmp = cal(i);
        if(tmp > Max){
            Max = tmp;
            ans.sz=0;
            pb(ans, i);
        }
        else if(tmp == Max)
            pb(ans, i);
    }
    printf("%d", Max);
    if(Max){
        for(int i=0; i<ans.sz; i++)
            printf(" %s", name[ans.ptr[i]]);
    }
    puts("");
}
int main(){
    while(scanf("%d", &n)==1){
        getchar();
        for(int i=0; i<n; i++){
            name[i] = getln();
            build(i);
        }
        build(n);
        solve();
    }
    return 0;
}
