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
int*t;
vec*e;

int go(int p){
    int mx=0;
    for(int z=0;z<e[p].sz;z++){int i=e[p].ptr[z];
        mx = fmax(mx, go(i));
    }
    return mx+t[p];
}
int numOfMinutes(int n, int headID, int*manager, int managerSz, int*informTime, int informTimeSz){
    t = informTime;
    e = calloc(n, sizeof(vec));
    for(int i=0; i<n; i++)
        if(i!=headID)
           pb(e[manager[i]], i);
    return go(headID);
}
