#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void reverse(char * str){
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}
/////////////////////////////
int main(){
    int n, d, w;
    scanf("%d %d %d", &n, &d, &w);
    vec word_len = newVec();
    int cur = 0;
    for(int i=0; i<n; ++i){
        char*s=getstr();
        if(i % 2 == 1)
            reverse(s);
        for(int z=0;s[z];z++){char j = s[z];
            if(j == '.'){
                if(cur > 0)
                    pb(word_len, cur);
                cur = 0;
            }
            else
                ++cur;
        }
    }
    if(cur > 0)
        pb(word_len, cur);
    int ans = 0;
    int col = 0;
    for(int z=0;z<word_len.sz;z++){int x = word_len.ptr[z];
        int new_col = col + (col > 0) + x;
        if(new_col > w){
            ++ans;
            new_col = x;
        }
        col = new_col;
    }
    printf("%d\n", ans+1);
    return 0;
}
