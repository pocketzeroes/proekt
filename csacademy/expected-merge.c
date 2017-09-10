#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
double *pushbackD(double *array, int *size, double value) {
    double *output = resizeArray(array, double, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct dvecS {
  double*ptr;
  int sz;
}vecd;
vecd newVecD() {
  vecd rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}

vecd resoudre(int m) {
    vecd res=newVecD();
    vecd t1 =newVecD();
    vecd t2 =newVecD();
    double n = (double) m;
    if (m == 1){
        res.ptr = pushbackD(res.ptr, &res.sz, 1.);
        return res;
    }
    else if (m % 2 == 0){
        t1 = resoudre(m/2);
        for (int i = 0; i < m/2; i++)
            res.ptr = pushbackD(res.ptr, &res.sz, t1.ptr[i]+n);
        for (int i = 0; i < m/2; i++)
            res.ptr = pushbackD(res.ptr, &res.sz, t1.ptr[i]+n);
    }
    else{
        t1 = resoudre(m/2);
        t2 = resoudre((m+1)/2);
        for (int i = 0; i < m/2; i++)
            res.ptr = pushbackD(res.ptr, &res.sz, (t1.ptr[i]+t2.ptr[i])/2+n);
        res.ptr = pushbackD(res.ptr, &res.sz , (t2.ptr[m/2] + t2.ptr[0])/2+n);
        for(int i = 0; i < m/2; i++)
            res.ptr = pushbackD(res.ptr, &res.sz , (t1.ptr[i] + t2.ptr[i+1])/2 + n);
    }
    return res;
}
int main() {
    int n;
    scanf("%d", &n);
    vecd res = resoudre(n);
    for (int i = 0; i < n; i++)
        printf("%lf ", res.ptr[i]);
    printf("\n");
    return 0;
}












