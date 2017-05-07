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

int minDistance(int height,int width,int*tree,int treeSize,int*squirrel,int squirrelSize,int**nuts,int nutsSz,int XX){
    vec nd  = newVec();
    vec sd  = newVec();
    int sum = 0;
    for(int i = 0; i < nutsSz; i++) {
        int tmp = abs(nuts[i][0] - tree[0]) + abs(nuts[i][1] - tree[1]);
        sum += tmp;
        nd.ptr=pushback(nd.ptr, &nd.sz, tmp);
        sd.ptr=pushback(sd.ptr, &sd.sz, abs(nuts[i][0] - squirrel[0]) + abs(nuts[i][1] - squirrel[1]));
    }
    int ans = -1;
    for (int i = 0; i < nutsSz; i++) {
        int tmp = sum * 2 - nd.ptr[i] + sd.ptr[i];
        if (ans == -1 || tmp < ans) 
            ans = tmp;
    }
    return ans;
}
