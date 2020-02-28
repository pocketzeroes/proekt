#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
#define pbp(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
pair*pushbackP(pair*array, int *size, pair value){
  pair*output = resizeArray(array, pair, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	pair*ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
enum{maxn = 200};
char str[maxn];
vecp s[maxn];
int n,m;

void exp2num(int idx){
    bool flag = true;
    for(int i = 0,ret = 0; str[i];){
        if(str[i] == '~')
            flag = false;
        if(isdigit(str[i])){
            while(isdigit(str[i]))
                ret = ret*10 + (str[i++]-'0');
            pbp(s[idx], newpair(ret-1,flag));
            ret = 0;
            flag = true;
        }
        else
            i++;
    }
}
bool check(int o){
    for(int i = 0; i < m; ++i){
        bool flag = false;
        for(int j = s[i].sz-1; j >= 0; --j){
            if(s[i].ptr[j].second == ((o>>s[i].ptr[j].first)&1)){
                flag = true;
                break;
            }
        }
        if(!flag)
            return false;
    }
    return true;
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d %d",&n,&m);
        getchar();
        for(int i = 0; i < m; ++i){
            s[i].sz=0;
            gets(str);
            exp2num(i);
        }
        bool ok = false;
        for(int i = 0; i < (1<<n) && !ok; ++i)
            ok = check(i);
        puts(ok?"satisfiable":"unsatisfiable");
    }
    return 0;
}
