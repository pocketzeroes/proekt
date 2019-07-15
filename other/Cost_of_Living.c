#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
double*pushback(double *array, int *size, double value) {
  double *output = resizeArray(array, double, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	double*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
vec *pushback2d(vec *array, int *size, vec value) {
  vec *output = resizeArray(array, vec, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  vec*ptr;
  int sz;
}vec2d;
vec2d newVec2d() {
  vec2d rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
void fill(double*arr, int sz, double val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
////////////////////////////////////////////
const double EPS = 1e-10;

double*solve(vec2d*M){
  int rows = M->sz,
      cols = M->ptr[0].sz;
  int rank = 0;
  for(int piv=0;piv<cols-1 && rank<rows;piv++){
    for(int i=rank;i<rows;i++){
      if(fabs(M->ptr[i].ptr[piv]) >= EPS){
        swap(M->ptr[rank].ptr, M->ptr[i].ptr);
        swap(M->ptr[rank].sz,  M->ptr[i].sz);
        break;
      }
    }
    if(fabs(M->ptr[rank].ptr[piv]) < EPS)
      continue;
    double divide_me = M->ptr[rank].ptr[piv];
    for(int j=rank;j<cols;j++)
      M->ptr[rank].ptr[j] /= divide_me;
    for(int i=0;i<rows;i++){
      if(fabs(M->ptr[i].ptr[piv]) < EPS || i == rank)
        continue;
      double multiplier = M->ptr[i].ptr[piv] / M->ptr[rank].ptr[piv];
      for(int j=rank;j<cols;j++)
        M->ptr[i].ptr[j] -= multiplier * M->ptr[rank].ptr[j];
    }
    rank++;
  }
  double*ans=calloc(cols-1,sizeof(double)); fill(ans, cols-1, -1);
  for(int i=0;i<rank;i++){
    int first = 0, 
        last  = cols-2;
    for(;first<cols;first++)
      if(fabs(M->ptr[i].ptr[first]) >= EPS)
        break;
    for(;last>=0;last--)
      if(fabs(M->ptr[i].ptr[last ]) >= EPS)
        break;
    if(first != last)
      continue;
    ans[first] = exp(M->ptr[i].ptr[cols-1]);
  }
  return ans;
}
int main(){
  int y, c, q;
  scanf("%d%d%d", &y, &c, &q);
  double r[y-1];
  for(int i=0; i<y-1; i++)
    scanf("%lf", &r[i]);
  double A[y][c];
  for(int i=0; i<y; i++)
    for(int j=0; j<c; j++)
      scanf("%lf", &A[i][j]);
  vec2d matrix=newVec2d();// of double
  for(int i=1; i<y; i++){
    for(int j=0; j<c; j++){
      vec row=newVec();
      row.ptr = calloc(y*c+y+c+1, sizeof(double));
      row.sz  = y*c+y+c+1;
      row.ptr[j*y + i]       =-1;
      row.ptr[j*y + (i-1)]   = 1;
      row.ptr[y*c + c + i-1] = 1;
      row.ptr[y*c + j]       = 1;
      matrix.ptr = pushback2d(matrix.ptr, &matrix.sz, row);
    }
  }
  for(int i=0;i<y;i++){
    for(int j=0;j<c;j++){
      if(A[i][j] >= -0.5){
        vec row=newVec();
        row.ptr = calloc(y*c+y+c+1, sizeof(double));
        row.sz = y*c+y+c+1;
        row.ptr[j*y + i] = 1;
        row.ptr[row.sz-1] = log(A[i][j]);
        matrix.ptr = pushback2d(matrix.ptr, &matrix.sz, row);
      }
    }
  }
  for(int i=0; i<y-1; i++){
    if(r[i] >= -0.5){
      vec row=newVec();
      row.ptr = calloc(y*c+y+c+1, sizeof(double));
      row.sz = y*c+y+c+1;
      row.ptr[y*c + c + i] = 1;
      row.ptr[row.sz-1] = log(r[i]);
      matrix.ptr = pushback2d(matrix.ptr, &matrix.sz, row);
    }
  }
  double*ans = solve(&matrix);
  while(q--){
    int a, b;
    scanf("%d%d", &a, &b);
    a--, b--;
    printf("%.10lf\n", ans[a*y+b]);
  }
  return 0;
}
