#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int**newmat(int x, int y){
  int**rv = calloc(x, sizeof(int*));
  for(int i=0; i<x; i++)
    rv[i] = calloc(y, sizeof(int));
  return rv;
}

void sort(int x, int y, int rows, int cols, int**mat){
    int arr[101]; clr(arr);
    int s=x, e=y;
    while(x < rows && y < cols){
        arr[mat[x][y]]++;
        x++;
        y++;
    }
    for(int i=0; i<101;){
        if(arr[i] <= 0){
            i++;
            continue;
        }
        if(arr[i] > 1){
            mat[s++][e++] = i;
            arr[i]--;
        }
        else
            mat[s++][e++] = i++;
    }
}
int**diagonalSort(int**mat, int matSz, int*mat0sz, int*rsz, int**csz){
    int m = matSz;
    int n = mat0sz[0];
    int**mrt = newmat(m, n);
    for(int i=0; i<m; i++)
      for(int j=0; j<n; j++)
        mrt[i][j] = mat[i][j];
    for(int i=n-1; i>=0; i--)
        sort(0, i, m, n, mrt);
    for(int i=1; i<m; i++)
        sort(i, 0, m, n, mrt);
    int*cols = calloc(m, sizeof(int)); fill(cols, m, n);
   *csz = cols;
   *rsz = m;
    return mrt;
}
