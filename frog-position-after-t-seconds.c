#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int*pushback(int*array, int*size, int value){
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
vec*v;

double dfs(int a, int b, double c, int d, int t){
    int hv = 0;
    for(int z=0;z<v[a].sz;z++){int i = v[a].ptr[z];
        if(i != d)
            hv++;
    }
    if(a == t){
        if(b > 0)
            return hv ? 0.0 : c;
        return b == 0 ? c : 0.0;
    }
    double ans = 0;
    for(int z=0;z<v[a].sz;z++){int i = v[a].ptr[z];
        if(i != d)
            ans += dfs(i, b - 1, c / hv, a, t);
    }
    return ans;
}
double frogPosition(int n, int**edges, int edgesSz, int*edges0sz, int t, int target){
    v=calloc(n, sizeof(vec));
    target--;
    for(int z=0;z<edgesSz;z++){int*i=edges[z];
       pb(v[i[0]-1], i[1]-1);
       pb(v[i[1]-1], i[0]-1);
    }
    return dfs(0, t, 1, -1, target);
}
