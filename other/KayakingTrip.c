#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
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

int N;

bool can(int minspeed, int b, int n, int e, int sb, int sn, int se, int*canoes){
    vec left = newVec();
    for(int z=0;z<N;z++){int c = canoes[z];
        int required = (minspeed + c - 1) / c;
        if(required > se + se)
            return false;
        if(sb + sb >= required){
            if(b >= 2){
                b -= 2;
                continue;
            }
        }
        if(sb + sn >= required){
            if(b >= 1 && n >= 1){
                b -= 1;
                n -= 1;
                continue;
            }
        }
        if(required > sn + se){
            if (e >= 2) {
                e -= 2;
                continue;
            }
            return false;
        }
        if(required > max(sn + sn, sb + se)){
            if(e >= 1 && n >= 1) {
                e -= 1;
                n -= 1;
                continue;
            }
            else if(e >= 2){
                e -= 2;
                continue;
            }
            return false;
        }
        left.ptr = pushback(left.ptr, &left.sz, c);
    }
    vec nleft = newVec();
    for(int z=0;z<left.sz;z++){int c = left.ptr[z];
        int required = (minspeed + c - 1) / c;
        if (sb + sn >= required){
            if (b == 0){
                if (n >= 2){
                    n -= 2;
                    continue;
                }
                if (n >= 1 && e >= 1){
                    n -= 1;
                    e -= 1;
                    continue;
                }
                if (e >= 2){
                    e -= 2;
                    continue;
                }
                return false;
            }
            if (n == 0){
                if (b >= 1 && e >= 1){
                    b -= 1;
                    e -= 1;
                    continue;
                }
                if (e >= 2){
                    e -= 2;
                    continue;
                }
                return false;
            }
        }
        nleft.ptr = pushback(nleft.ptr, &nleft.sz, c);
    }
    for(int z=0;z<nleft.sz;z++){int c = nleft.ptr[z];
        int required = (minspeed + c - 1) / c;
        if (se + sb < sn + sn) {
            if (se + sb >= required && e >= 1 && b >= 1) {
                b -= 1;
                e -= 1;
                continue;
            }
            if (sn + sn >= required && n >= 2) {
                n -= 2;
                continue;
            }
        }
        else {
            if (se + sb >= required && e >= 1 && b >= 1) {
                b -= 1;
                e -= 1;
                continue;
            }
            if (sn + sn >= required && n >= 2) {
                n -= 2;
                continue;
            }
        }
        if (sn + se >= required && e >= 1 && n >= 1) {
            n -= 1;
            e -= 1;
            continue;
        }
        if (se + se >= required && e >= 2) {
            e -= 2;
            continue;
        }
        return false;
    }
    return true;
}
int main(){
    int b  = in_nextInt();
    int n  = in_nextInt();
    int e  = in_nextInt();
    int sb = in_nextInt();
    int sn = in_nextInt();
    int se = in_nextInt();
    N  = (b + n + e) / 2;
    int canoes[N];
    for(int i = 0; i < N; ++i)
        canoes[i] = in_nextInt();
    qsort(canoes, N, sizeof(int), cmp);
    int lo = 1;
    int hi = 300000000;
    while(hi - lo > 1){
        int mid = (lo + hi) / 2;
        if(can(mid, b, n, e, sb, sn, se, canoes))
            lo = mid;
        else
            hi = mid;
    }
    printf("%d\n", lo);
    return 0;
}
