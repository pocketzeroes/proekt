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
////////////////////////////////////
int D[101010];
vec E[101010];

void dfs(int cur, int pre, int d){
    D[cur]=d;
    for(int z=0;z<E[cur].sz;z++){int e=E[cur].ptr[z];
        if(e!=pre)
            dfs(e, cur, d+1);
    }
}
int minReorder(int n, int**connections, int connectionsSz, int*connections0sz){
    int i;
    for(i=0; i<n; i++)
        E[i].sz=0;
    for(int z=0;z<connectionsSz;z++){int*c=connections[z];
        pb(E[c[0]], c[1]);
        pb(E[c[1]], c[0]);
    }
    dfs(0, 0, 0);
    int ret=0;
    for(int z=0;z<connectionsSz;z++){int*c=connections[z];
        if(D[c[0]]<D[c[1]])
            ret++;
    }
    return ret;
}
