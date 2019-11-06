#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ __typeof(a) tp; tp = a; a = b; b = tp; }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
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
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

/////////////////////////////

int moveind[128];
int moves  [4];
enum{ INF = 1000000000};

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    char*lin = strdup("");
    for(int i=0; i<M+2; i++)
        lin = concatc(lin, '#');
    for(int i=0; i<N; i++){
        char*inp = getstr();
        lin = concats(lin, inp);
        lin = concatc(lin, '#');
    }
    for(int i=0; i<M+2; i++)
        lin = concatc(lin, '#');
    int st  = 0;
    int end = 0;
    for(int i=0; lin[i]; i++)
        if(lin[i] == 'S')
          st = i;
        else if(lin[i] == 'G')
          end = i;
    char*cmd = getstr();
    int  cmd_size = strlen(cmd);
    moveind['L'] = -1;
    moveind['R'] = 1;
    moveind['U'] = -M-1;
    moveind['D'] = M+1;
    moves[0]     = -1;
    moves[1]     = 1;
    moves[2]     = -M-1;
    moves[3]     = M+1;
    int atmod = strlen(lin);
    int cost[atmod*(cmd_size+1)]; fill(cost, atmod*(cmd_size+1), INF);
    vec thislev = newVec();
    pb(thislev, st);
    cost[st] = 0;
    int finished = -1;
    for(int d=0; finished<0; d++){
        for(int i=0; i<thislev.sz; i++){
            int at    = thislev.ptr[i];
            int sqat  = at % atmod;
            int cmdat = at / atmod;
            if(cmdat < cmd_size){
                int nsq = sqat + moveind[cmd[cmdat]];
                if(nsq == end)
                    finished = d;
                if(lin[nsq] == '#')
                    nsq = sqat;
                int st2 = nsq + (cmdat + 1) * atmod;
                if(cost[st2] > d){
                    cost[st2] = d;
                    pb(thislev, st2);
                }
            }
        }
        vec nextlev = newVec();
        for(int i=0; finished < 0 && i<thislev.sz; i++){
            int at   = thislev.ptr[i];
            int sqat = at % atmod;
            for(int mv=0; mv<4; mv++){
                int nsq = sqat + moves[mv];
                if(nsq == end)
                    finished = d + 1;
                int nat = at + moves[mv];
                if(lin[nsq] != '#' && cost[nat] > d + 1){
                    cost[nat] = d + 1;
                    pb(nextlev, nat);
                }
            }
        }
        swap(thislev.ptr, nextlev.ptr);
        swap(thislev.sz,  nextlev.sz);
        nextlev.sz=0;
        free(nextlev.ptr);
        nextlev.ptr=NULL;
        if(thislev.sz == 0)
            break;
    }
    printf("%d\n", finished);
    return 0;
}
