#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[100000];
char*getstr(){
  int rv = scanf("%s", &buff);
  return strdup(buff);
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


/////////////////////////
int N;
int n_i = 0;
char*stations[33];
bool conn[33][33];

int get_i_st(char*st){
    for(int i = 0; i < n_i; i++)
        if(strcmp(stations[i], st)==0)
            return i;
    stations[n_i] = strdup(st);
    n_i++;
    return n_i-1;
}
bool arrive(int des, vec*vis){
    int o = vis->ptr[vis->sz-1];
    if(o == des)
        return true;
    for(int i=0; i<n_i; i++){
        bool has = false;
        for(int z=0;z<vis->sz;z++){int v = vis->ptr[z];
            if (v == i){
                has = true;
                break;
            }
        }
        if(!has && conn[o][i]){
            vis->ptr = pushback(vis->ptr, &vis->sz, i);
            bool arr = arrive(des, vis);
            if(arr)
                return true;
            else
                vis->sz--;
        }
    }
    return false;
}
int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        char*station=getstr();
        int i_st = get_i_st(station);
        while(1){
            char c = getchar();
            if(c == '\n') break;
            ungetc(c, stdin);
            char*s = getstr();
            int _i_st = get_i_st(s);
            conn[i_st][_i_st] = true;
            conn[_i_st][i_st] = true;
        }
    }
    int ori;
   {char*_ori=getstr();
    ori = get_i_st(_ori);}
    int des;
   {char*_des=getstr();
    des = get_i_st(_des);}
    vec vistied = newVec();
    pb(vistied, ori);
    bool arr = arrive(des, &vistied);
    if(arr){
        for(unsigned i = 0; i < vistied.sz; i++){
            printf("%s", stations[vistied.ptr[i]]);
            if(i < vistied.sz - 1)
                printf(" ");
            else
                puts("");
        }
    }
    else
        puts("no route found");
    return 0;
}
