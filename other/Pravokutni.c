#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
enum{ MAX = 1500};
typedef struct{
   ll dx, dy;
   int quadrant;
}ray;
void rotate90(ray*r){
   ll tmp = r->dx;
   r->dx = r->dy;
   r->dy = -tmp;
   r->quadrant = (r->quadrant+1)%4;
}
int cmpR(const void*pa, const void*pb){
   ray*A=(ray*)pa;
   ray*B=(ray*)pb;
   if(A->dy*B->dx == B->dy*A->dx)
      return 0;
   return(A->dy*B->dx <  B->dy*A->dx)?-1:1;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
ray*pushbackR(ray*array, int *size, ray value){
  ray*output = resizeArray(array, ray, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	ray*ptr;
	int sz;
}vecr;
vecr newVecR(){
	vecr rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int n;
int x[MAX],
    y[MAX];
int main(){
   scanf("%d", &n);
   for(int i = 0; i < n; ++i)
      scanf("%d%d", &x[i], &y[i]);
   int solution = 0;
   for(int i = 0; i < n; ++i){
      vecr rays = newVecR();//of ray
      for(int j = 0; j < n; ++j){
         if( i == j )
            continue;
         ray R;
         R.quadrant = 0;
         R.dx = x[j]-x[i];
         R.dy = y[j]-y[i];
         while(!(R.dx > 0 && R.dy >= 0))
            rotate90(&R);
         rays.ptr = pushbackR(rays.ptr, &rays.sz, R);
      }
      qsort(rays.ptr, rays.sz, sizeof(ray), cmpR);
      int count[4];
      for(int j=0, k; j<rays.sz; j = k){
         count[0] = count[1] = count[2] = count[3] = 0;
         for(k = j; k<rays.sz && cmpR(&rays.ptr[j], &rays.ptr[k])==0; ++k)
            ++count[rays.ptr[k].quadrant];
         solution += count[0] * count[1];
         solution += count[1] * count[2];
         solution += count[2] * count[3];
         solution += count[3] * count[0];
      }
   }
   printf("%d\n", solution);
   return 0;
}
