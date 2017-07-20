#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<limits.h>
#include<stdbool.h>

#define f first
#define s second
#define mp make_pair
#define pb pushback
#define lp(i,a,n) for(int i=(a);i<=(int)(n);++i)
#define lpd(i,a,n) for(int i=(a);i>=(int)(n);--i)
#define mem(a,b) memset(a,b,sizeof a)
#define all(v) v.begin(),v.end()
#define println(a) cout <<(a) <<endl
#define readi(x) scanf("%d",&x)
#define read2i(x,y) scanf("%d%d",&x,&y)
#define read3i(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define readll(x) scanf("%I64d",&x)
#define mod 1000000007
#define eps 1e-6
#define infi 1000000000
#define infll 1000000000000000000ll


void swap(int*nums, int i, int j) {
  int t   = nums[i];
  nums[i] = nums[j];
  nums[j] = t;
}

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;// = malloc(sizeof(vec));
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}


enum{ N = 100002};
int n,k,a[N];

bool check(int i){
    if(i > 1 && abs(a[i] - a[i-1]) > k) return false;
    if(i < n && abs(a[i] - a[i+1]) > k) return false;
    return true;
}
int main(){
    read2i(n,k);
    lp(i,1,n) readi(a[i]);
    vec bad=newVec();
    lp(i,2,n) 
      if(abs(a[i] - a[i-1]) > k) 
          bad.ptr = pb(bad.ptr, &bad.sz ,i);
    if(bad.sz && bad.ptr[0] == 2) 
        bad.ptr = pb(bad.ptr, &bad.sz ,1);
    if(!bad.sz)     return puts("0")*0;
    if(bad.sz > 10) return puts("-1")*0;
    for(int z=0;z<bad.sz;z++){ int j = bad.ptr[z];
        lp(i,1,n){
            swap(a, i, j);
            bool ok = check(i);
            for(int q=0;q<bad.sz;q++){ int k = bad.ptr[q];
                ok &= check(k);
            }
            if(ok) 
                return printf("%d %d", i, j) * 0;
            swap(a, i, j);
        }
    }
    puts("-1");
}






















































