#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize){
    int*sz=malloc(sizeof(int));
   *sz=0;
    int m = matrixRowSize;
    int*res=NULL;
    if (m == 0) 
        return res;
    int n = matrixColSize;
    typedef enum Act {RIGHT, DOWN, LEFT, UP}Action;
    Action action = RIGHT;
    for (int i = 0, j = 0, begini = 0, beginj = 0, endi = m, endj = n, cnt = 0, total = m * n; cnt < total; ++cnt) {
        res = pushback(res, sz, matrix[i][j]);
        switch (action) {
          case RIGHT:
              if (j + 1 < endj) 
                  ++j;
              else 
                  action = DOWN, ++begini, ++i;
              break;
          case DOWN:
              if (i + 1 < endi) 
                  ++i;
              else
                  action = LEFT, --endj, --j;
              break;
          case LEFT:
              if (j - 1 >= beginj) 
                  --j;
              else
                  action = UP, --endi, --i;
              break;
          case UP:
              if (i - 1 >= begini)
                  --i;
              else
                  action = RIGHT, ++beginj, ++j;
              break;
          default:
              break;
        }
    }
    return res;
}








