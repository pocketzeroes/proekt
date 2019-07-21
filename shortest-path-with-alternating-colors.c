int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

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
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int D[101][2];

int*shortestAlternatingPaths(int n, int**red_edges, int red_edgesSz, int*red_edges0sz, int**blu_edges, int blu_edgesSz, int*blu_edges0sz, int*rsz){
    int i,j,k;
    for(j=0; j<n; j++)
        D[j][0] = D[j][1] = 1<<20;
    D[0][0] = D[0][1] = 0;
    for(i=0; i<2*n; i++){
        for(int z=0;z<red_edgesSz;z++){int*e=red_edges[z];
            D[e[1]][1] = min(D[e[1]][1],D[e[0]][0]+1);
        }
        for(int z=0;z<blu_edgesSz;z++){int*e=blu_edges[z];
            D[e[1]][0] = min(D[e[1]][0],D[e[0]][1]+1);
        }
    }
    vec V = newVec();
    for(i=0; i<n; i++){
        int v = min(D[i][0], D[i][1]);
        if(v==1<<20)
            v = -1;
        V.ptr = pushback(V.ptr, &V.sz, v);
    }
   *rsz=   V.sz;
    return V.ptr;
}
