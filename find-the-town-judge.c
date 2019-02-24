#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int findJudge(int N, int**trust, int trustSz, int*trust0sz){
    bool adj[N + 1][N + 1]; memset(adj, 0, sizeof(adj));
    for(int z=0; z<trustSz; z++){int*t = trust[z];
        adj[t[0]][t[1]] = true;
    }
    vec judges = newVec();
    for(int i=1; i<=N; i++){
        bool works = true;
        for(int j=1; j<=N; j++){
            if (j != i) {
                if (!adj[j][i]) {
                    works = false;
                    break;
                }
                if (adj[i][j]) {
                    works = false;
                    break;
                }
            }
        }
        if (works)
            judges.ptr = pushback(judges.ptr, &judges.sz, i);
    }
    if(judges.sz != 1)
        return -1;
    return judges.ptr[0];
}
