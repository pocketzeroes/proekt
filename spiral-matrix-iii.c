int*newPair(int a, int b){
  int*rez = calloc(2, sizeof(int));
  rez[0] = a;
  rez[1] = b;
  return rez;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int**pushbackP(int**array, int*size, int*value){
  int**output = resizeArray(array, int*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int**ptr;
	int sz;
}vecp;
vecp newVecP(){
	vecp rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

const int d[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

bool valid(int x, int y, int n, int m){
    return x >= 0 && x < n && y >= 0 && y < m;
}
int**spiralMatrixIII(int n, int m, int x, int y, int**colszs, int*rsz){
    vecp ret = newVecP();
    ret.ptr = pushbackP(ret.ptr, &ret.sz, newPair(x, y));
    int dir = 0;
    for(int k=1; ; ++k){
        for(int i=0; i<k; ++i){
            x += d[dir][0];
            y += d[dir][1];
            if(valid(x, y, n, m))
                ret.ptr = pushbackP(ret.ptr, &ret.sz, newPair(x, y));
            if(ret.sz == n * m)
               goto return_ret;
        }
        dir = (dir + 1) % 4;
        for(int i=0; i<k; ++i){
            x += d[dir][0];
            y += d[dir][1];
            if(valid(x, y, n, m))
                ret.ptr = pushbackP(ret.ptr, &ret.sz, newPair(x, y));
            if(ret.sz == n * m)
               goto return_ret;
        }
        dir = (dir + 1) % 4;
    }
return_ret:;
    int*cols = calloc(ret.sz,sizeof(int));
    for(int i=0;i<ret.sz;i++)
        cols[i]=2;
   *colszs= cols;
   *rsz =  ret.sz;
    return ret.ptr;
}
