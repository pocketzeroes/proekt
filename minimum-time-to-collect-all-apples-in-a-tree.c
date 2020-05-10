#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
///////////////////////////////
vec E[101010];
bool*H;
int ret;

int dfs(int cur, int pre){
    int take=H[cur];
    for(int z=0;z<E[cur].sz;z++){int e=E[cur].ptr[z];
        if(e!=pre)
            take |= dfs(e,cur);
    }
    if(take&&cur)
        ret+=2;
    return take;
}
int minTime(int n, int**edges, int edgesSz, int*edges0sz, bool*hasApple, int hasAppleSz){
    H=hasApple;
    int N=hasAppleSz;
    int i;
    for(i=0; i<N; i++)
        E[i].sz=0;
    for(int z=0; z<edgesSz; z++){int*e=edges[z];
       pb(E[e[0]], e[1]);
       pb(E[e[1]], e[0]);
    }
    ret=0;
    dfs(0, -1);
    return ret;
}
