#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

typedef int* intp;
#define pb(zpv, zvv) zpv.ptr = pushbackP(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
intp*pushbackP(intp*array, int*size, intp value){
  intp*output = resizeArray(array, intp, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
    intp*ptr;
    int sz;
}vecp;
vecp newVecP(){
    vecp rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}
intp newp(int a, int b){
    int*rv=calloc(2, sizeof(int));
    rv[0]=a;
    rv[1]=b;
    return rv;
}

int**queensAttacktheKing(int**queens, int queensSz, int*queens0sz, int*king, int kingSz, int*rsz, int**cszs){
    int g[8][8]; clr(g);
    for(int z=0;z<queensSz;z++){int*it = queens[z];
        g[it[0]][it[1]] = 1;
    }
    int X[8] = {-1,-1,-1,0,0,1,1,1};
    int Y[8] = {-1,0,1,-1,1,-1,0,1};
    vecp res = newVecP();
    for(int i=0; i<8; i++){
        for(int k=1;;k++){
            int x = X[i]*k+king[0],
                y = Y[i]*k+king[1];
            if(x>=0&&x<8&&y>=0&&y<8){
                if(g[x][y]){
                    pb(res, newp(x,y));
                    break;
                }
            }
            else
                break;
        }
    }
    int*cols=calloc(res.sz, sizeof(int));
    fill(cols, res.sz, 2);
   *cszs = cols;
   *rsz=   res.sz;
    return res.ptr;
}
