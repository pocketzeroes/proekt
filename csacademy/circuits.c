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
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}




/////////////////////
typedef long long ll;
enum{ MAX_N = 19};
enum{ NBS_END = -5};
bool visStates[MAX_N][(1 << MAX_N)];
int n;
ll dp[MAX_N][(1 << MAX_N)];
vec nbs[MAX_N];

int find(int*arr, int sz, int what){
    for(int i=0;i<sz;i++){
        if(arr[i]==what)
            return i;
    }
    return NBS_END;
}
bool IsMarkedBit(int mask, int bit) {
    return ((mask & (1 << bit)) != 0);
}
int MarkBit(int mask, int bit) {
    return (mask | (1 << bit));
}
ll ComputeDp(int currNode, int visNodes) {
    if(visNodes == (1 << n) - 1){
        if(find(nbs[currNode].ptr, nbs[currNode].sz, 1) != NBS_END) {
            dp[currNode][visNodes] = 1ll;
            return 1ll;
        }
        else{
            dp[currNode][visNodes] = 0ll;
            return 0ll;
        }
    }
    else if(visStates[currNode][visNodes]){
        return dp[currNode][visNodes];
    }
    dp[currNode][visNodes] = 0;
    for(int z=0;z<nbs[currNode].sz;z++){ int x = nbs[currNode].ptr[z];
        if(!IsMarkedBit(visNodes, x - 1))
            dp[currNode][visNodes] += ComputeDp(x, MarkBit(visNodes, x - 1));
    }
    visStates[currNode][visNodes] = true;
    return dp[currNode][visNodes];
}
int main(){
    int m;
    ll k;
    scanf("%d %d %lld", &n, &m, &k);
    for(int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        nbs[x].ptr = pushback(nbs[x].ptr, &nbs[x].sz, y);
    }
    for(int i = 1; i <= n; i++){
        qsort(nbs[i].ptr, nbs[i].sz, sizeof(int), cmp);
    }
    ComputeDp(1, 1);
    int currNode = 1, visNodes = 1;
    vec ans = newVec();
    ans.ptr = pushback(ans.ptr, &ans.sz, currNode);
    while(visNodes != (1 << n) - 1) {
        bool changed = false;
        for(int z=0;z<nbs[currNode].sz;z++){ int x = nbs[currNode].ptr[z];
            if(!IsMarkedBit(visNodes, x - 1)) {
                if(dp[x][MarkBit(visNodes, x - 1)] >= k) {
                    currNode = x;
                    visNodes = MarkBit(visNodes, x - 1);
                    changed = true;
                    break;
                }
                else
                    k -= dp[x][MarkBit(visNodes, x - 1)];
            }
        }
        if(!changed){
            puts("0");
            return 0;
        }
        ans.ptr = pushback(ans.ptr, &ans.sz, currNode);
    }
    ans.ptr = pushback(ans.ptr, &ans.sz, 1);
    for(int i=0;i<ans.sz;i++){ int x = ans.ptr[i];
        printf("%d ", x);
    }
    puts("");
    return 0;
}






























