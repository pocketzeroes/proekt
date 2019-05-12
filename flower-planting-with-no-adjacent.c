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
///////////////
int color[22222];
vec edge[22222];

void dfs(int x){
    int seen[5] = {0};
    for(int z=0;z<edge[x].sz;z++){int it=edge[x].ptr[z];
        seen[color[it]] = 1;
    }
    int c = 1;
    while(seen[c])
        ++c;
    color[x] = c;
    for(int z=0;z<edge[x].sz;z++){int it=edge[x].ptr[z];
        if (!color[it])
            dfs(it);
    }
}
int*gardenNoAdj(int n, int**paths, int pathsSz, int*paths0sz, int*rsz){
    for(int i=0; i<n; i++){
        color[i] = 0;
        edge[i].sz=0;
    }
    for(int z=0;z<pathsSz;z++){int*it=paths[z];
        int u = it[0];
        int v = it[1];
        --u, --v;
        edge[u].ptr = pushback(edge[u].ptr, &edge[u].sz, v);
        edge[v].ptr = pushback(edge[v].ptr, &edge[v].sz, u);
    }
    for(int i=0; i<n; i++)
        if (!color[i])
            dfs(i);
    vec result=newVec();
    for(int i=0; i<n; i++)
        result.ptr = pushback(result.ptr, &result.sz, color[i]);
   *rsz =  result.sz;
    return result.ptr;
}
