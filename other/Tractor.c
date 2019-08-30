#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define pb(zpv, zvv) zpv.ptr = pushbackB(zpv.ptr, &zpv.sz, zvv)
#define swap(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
bool*pushbackB(bool*array, int *size, bool value){
  bool*output = resizeArray(array, bool, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	bool*ptr;
	int sz;
}vecb;
vecb newVecB(){
	vecb rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


int ff(bool*src, int pos){
    int res = 0, rad = 1;
    for(int i=0;i<pos;++i){
        if(src[i])
            res += rad;
        rad*=2;
    }
    return res;
}
int main(){
    int n,aa,bb;
    scanf("%d", &n);
    while(n--){
        scanf("%d %d", &aa, &bb);
        if(aa<bb){
            swap(aa, bb);
        }
        int originalA = aa,
            originalB = bb;
        vecb a=newVecB();
        vecb b=newVecB();
        while(aa){
            pb(a, aa%2);
            aa/=2;
        }
        while(bb){
            pb(b, bb%2);
            bb/=2;
        }
        int k = b.sz, kk = 1;
        for(int i=1;i<=k;++i)
            kk*=2;
        int res = kk - 1;
        int bprime = originalB - kk/2 + 1;
        int aprime = kk/2;
        if(a.sz == b.sz){
            aprime = originalA - kk/2 + 1;
            res+=(aprime+bprime);
        }
        else{
            res += (a.sz-b.sz)*(aprime+bprime);
            bool check = true;
            for(int i=a.sz-1;i>=b.sz && check; --i)
                if(!a.ptr[i])
                    check = false;
            for(int i=b.sz-1;i>=0 && check; --i)
                if(!a.ptr[i] && !b.ptr[i]){
                    check = false;
                    break;
                }
                else if(a.ptr[i]&&b.ptr[i]){
                    check = false;
                    res+= ff(b.ptr, i)+
                          ff(a.ptr, i)+2;
                    break;
                }
            if(check)
                res++;
        }
        printf("%d\n", res);
    }
    return 0;
}
