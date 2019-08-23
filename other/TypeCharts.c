#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}
char*string(int num, char chr){
  char spce[num+1]; memset(spce, chr, sizeof(spce)); spce[num]='\0';
  return strdup(spce);
}

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

enum{ MAXE =(int)1.1e5};
enum{ MAXN =(int)1.1e5};
char*result_string;
bool has_types[MAXN][4];
int  mark[MAXN];
vec adj[MAXN];

int get_type(char c){
    if(c == 'x')return 0;
    if(c == '-')return 1;
    if(c == '=')return 2;
    if(c == '+')return 3;
    assert(false);
    return -1;
}
bool check_bipartite(int n, vec*p0, vec*p1, int c){
    if(mark[n] != -1)
        return mark[n] == c;
    p0->ptr = pushback(p0->ptr, &p0->sz, n);
    mark[n] = c;
    bool res = true;
    for(int z=0;z<adj[n].sz;z++){int to = adj[n].ptr[z];
        res &= check_bipartite(to, p1, p0, 5-c);
    }
    return res;
}
int main(){
    int N,M;
    scanf("%d %d", &N, &M);
    result_string = string(N,' ');
    for(int i = 0; i < N; i++)
        mark[i] = -1;
    memset(has_types, 0, sizeof(has_types));
    for(int m=0; m<M; m++){
        int a, b, c;
        char*s;
        scanf("%d %d", &a, &b);
        s=getstr();
        c = get_type(s[0]);
        has_types[--a][c] = 1;
        has_types[--b][c] = 1;
        if(c == 2){
            adj[a].ptr = pushback(adj[a].ptr, &adj[a].sz, b);
            adj[b].ptr = pushback(adj[b].ptr, &adj[b].sz, a);
        }
    }
    for(int i=0; i<N; i++){
        if(mark[i] == -1){
            if(!has_types[i][1] && !has_types[i][2] && !has_types[i][3]){
                result_string[i] = 'x';
                mark[i] = i;
            }
            else if(mark[i] == -1){
                vec p0 = newVec();
                vec p1 = newVec();
                bool bp = check_bipartite(i, &p0, &p1, -2);
                for(int z=0; z<p0.sz; z++){int it = p0.ptr[z];
                    for(int j = 1; j < 4; j++)
                        has_types[i][j] |= has_types[it][j];
                }
                for(int z=0; z<p1.sz; z++){int it = p1.ptr[z];
                    for(int j = 1; j < 4; j++)
                        has_types[i][4-j] |= has_types[it][j];
                }
                if(!bp || (has_types[i][1] && has_types[i][3])){
                    for(int z=0; z<p0.sz; z++){int it = p0.ptr[z];
                        result_string[it] = '=';
                    }
                    for(int z=0; z<p1.sz; z++){int it = p1.ptr[z];
                        result_string[it] = '=';
                    }
                }
                else if(has_types[i][1]){
                    for(int z=0; z<p0.sz; z++){int it = p0.ptr[z];
                        result_string[it] = '-';
                    }
                    for(int z=0; z<p1.sz; z++){int it = p1.ptr[z];
                        result_string[it] = '+';
                    }
                }
                else {
                    for(int z=0; z<p0.sz; z++){int it = p0.ptr[z];
                        result_string[it] = '+';
                    }
                    for(int z=0; z<p1.sz; z++){int it = p1.ptr[z];
                        result_string[it] = '-';
                    }
                }
            }
        }
    }
    puts(result_string);
	return 0;
}
