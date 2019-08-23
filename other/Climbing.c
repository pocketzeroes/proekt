#define _GNU_SOURCE 1
#include<stdio.h>    // climbing
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
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
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}


int n;
int* preds [1005];
bool active[1005][1005];

vec sequence(int ofs, int n){
    if(n == 1){
        vec rv = newVec();
        rv.ptr = pushback(rv.ptr, &rv.sz, 1+ofs);
        return rv;
    }
    else{
        vec a = sequence(ofs, n/2);
        vec b = sequence(ofs + n/2, n - n/2);
        vec re = newVec();
        for(int i=0; i<a.sz; i++)
            re.ptr=pushback(re.ptr, &re.sz, a.ptr[i]);
        for(int i=0; i<b.sz; i++)
            re.ptr=pushback(re.ptr, &re.sz, b.ptr[i]);
        for(int i=a.sz-1; i>=0; i--)
            re.ptr=pushback(re.ptr, &re.sz, a.ptr[i]);
        return re;
    }
}
int main(){
    scanf("%d", &n);
    for(int x=1; x<=n; x++){
        int npreds;
        scanf("%d", &npreds);
        preds[x]=calloc(npreds, sizeof(int));
        for(int i=0; i<npreds; i++)
            scanf("%d", &preds[x][i]);
    }
    int le;
    scanf("%d", &le);
    int seq[1+le]; clr(seq);
    clr(active);
    for(int i=1; i<=le; i++){
        scanf("%d", &seq[i]);
        for(int x=1; x<=n; x++)
            active[i][x]  =  active[i-1][x];
        active[i][seq[i]] = !active[i][seq[i]];
    }
    char*s = strdup("x");
    for(int i=0;i<le;i++)
        s = concatc(s, '.');
    int counter[n+1]; clr(counter);
    vec answer = newVec();
    vec sq = sequence(0, le);
    for(int z=0;z<sq.sz;z++){int pos = sq.ptr[z];
        if(s[pos] == '.'){
           s[pos] = 'x';
            for(int x=1;x<=n;x++){
                if(active[pos][x]) {
                    if(counter[x]==0)
                        answer.ptr = pushback(answer.ptr, &answer.sz, x);
                    counter[x]++;
                }
            }
        } 
        else{
            s[pos] = '.';
            for (int x=1;x<=n;x++){
                if (active[pos][x]) {
                    if (counter[x]==1)
                        answer.ptr = pushback(answer.ptr, &answer.sz, x);
                    counter[x]--;
                }
            }
        }
    }
    printf("%d\n", answer.sz);
    for(int z=0;z<answer.sz;z++)
        printf("%d\n", answer.ptr[z]);
    return 0;
}
