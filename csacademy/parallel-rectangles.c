#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stddef.h>
#include<stdbool.h>
#include<limits.h>
int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
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
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef long long ll;
enum{ N = 100000};
enum{ S = 200   };
int n;
int x[100000], y[100000];
vec v[100000], z[100000];
int b[100000];

int main() {
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) 
        scanf("%d%d", x + i, y + i), --x[i], --y[i];
    for(int i = 0; i < n; ++i){
        int idx=x[i];
        v[idx].ptr = pushback(v[idx].ptr, &v[idx].sz, y[i]);
    }
    for(int i = 0; i < N; ++i) 
        qsort(v[i].ptr, v[i].sz, sizeof(int), cmp);
    ll ans = 0;
    for(int i = 0; i < (N); ++i) 
        if(v[i].sz > S){
          for(int q=0;q<v[i].sz;q++){int x = v[i].ptr[q];
            ++b[x];
          }
          for(int j = 0; j < (N); ++j) 
            if (j > i || v[j].sz <= S){
                int cnt = 0;
                for(int q=0;q<v[j].sz;q++){int x = v[j].ptr[q];
                    cnt += b[x];
                }
                ans += (ll)cnt * (cnt - 1) / 2;
            }
          for(int q=0;q<v[i].sz;q++){int x = v[i].ptr[q];
              --b[x];
          }
        }
    for (int i = 0; i < (N); ++i) 
      if (v[i].sz <= S){
        for(int q=0;q<v[i].sz;q++){int x = v[i].ptr[q];
            for(int q2=0;q2<v[i].sz;q2++){int y = v[i].ptr[q2];
              if(y == x) 
                break;
              z[x].ptr = pushback(z[x].ptr, &z[x].sz, y);
            }
        }
      }
    for (int i = 0; i < (N); ++i) 
      if(z[i].sz>0){
        for(int q=0;q<z[i].sz;q++){int x = z[i].ptr[q];
            ans += b[x];
            ++b[x];
        }
        for(int q=0;q<z[i].sz;q++){int x = z[i].ptr[q];
            --b[x];
        }
      }
    printf("%lld\n", ans);
    return 0;
}





















