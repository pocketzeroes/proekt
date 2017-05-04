#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>


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
pair*pushbackP(pair*array, int *size, pair value){
    pair*output = resizeArray(array, pair, *size + 1);
    output[(*size)++] = value;
    return output;
}
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	pair*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


typedef long long int64;
enum{ kMaxN =(int) 1e5+5};
vec vertex[kMaxN];

int64 Solve(int n, int cost){
    int64 ans = 0;
    bool visited[n + 1];
    memset(visited,0,sizeof(visited));
    for(int i = 1; i <= n; i++){
        if (visited[i]) 
            continue;
        int*queue=NULL;int queueSz=0;
        queue = pushback(queue, &queueSz, i);
        visited[i] = true;
        int q_size = 1;
        while(queueSz){
            int node = queue[queueSz-1];
            queueSz--;
            for(int i=0; i<vertex[node].sz;i++){pair edge = vertex[node].ptr[i];
                if (edge.second > cost)
                    continue;
                int oth = edge.first;
                if(visited[oth])
                    continue;
                else{
                    queue=pushback(queue, &queueSz, oth);
                    visited[oth] = true;
                    q_size += 1;
                }
            }
        }
        ans += 1LL * q_size * (q_size - 1) / 2;
    }
    return ans;
}
int main(){
    int n, m, x;
    scanf("%d %d %d", &n, &m, &x);
    for (int i = 0; i < m; i += 1) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        vertex[a].ptr=pushbackP(vertex[a].ptr, &vertex[a].sz, newPair(b, c));
        vertex[b].ptr=pushbackP(vertex[b].ptr, &vertex[b].sz, newPair(a, c));
    }
    int64 small = Solve(n, x - 1);
    int64 big   = Solve(n, x    );
    printf("%lld\n", big - small);
    return 0;
}























































