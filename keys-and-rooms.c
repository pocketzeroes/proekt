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

bool canVisitAllRooms(int**rooms, int roomsSz, int*rooms0sz){
    int N = roomsSz;
    if (N == 0)
        return true;
    char use[N]; memset(use,0,sizeof(use));
    use[0] = true;
    vec ord = newVec();
    ord.ptr = pushback(ord.ptr, &ord.sz, 0);
    for(int i=0; i<ord.sz; i++){
        int v = ord.ptr[i];
        for(int z=0; z<rooms0sz[v]; z++){int e = rooms[v][z];
            if(!use[e]){
                use[e] = true;
                ord.ptr = pushback(ord.ptr, &ord.sz, e);
            }
        }
    }
    return ord.sz == N;
}
