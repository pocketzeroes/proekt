#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define swap(a,b) do{ typeof(a) tp; tp = a; a = b; b = tp; }while(0)
#define copyVec(best, vis) do{ \
                if(best.ptr)free(best.ptr); \
                best.sz = vis.sz;\
                best.ptr = calloc(vis.sz, sizeof(int)); \
                for(int i=0; i<vis.sz; i++) \
                    best.ptr[i] = vis.ptr[i]; \
}while(0)

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


#define bitset_elem(ptr,bit) ((unsigned char *)(ptr))[(bit)/CHAR_BIT]
#define bitset_mask(bit) (1U << ((bit) % CHAR_BIT))
int bitset_isset(void *ptr, int bit){
  return (bitset_elem(ptr,bit) & bitset_mask(bit)) != 0;
}
int bitset_set(void *ptr, int bit){
  unsigned char *b = (unsigned char *)ptr + (bit / CHAR_BIT);
  unsigned char m = bitset_mask(bit);
  if ((*b & m)) return 0;
  *b |= m;
  return 1;
}
char p[32];

int main(){
  int n, m;
  scanf("%d %d", &n, &m);
  while(m--){
    int k;
    scanf("%d", &k);
    bitset_set(p, k);
  }
  vec a = newVec();
  for(int mask = (0); mask < (1 << n); mask++)
    if(bitset_isset(p, __builtin_popcount(mask)))
      a.ptr = pushback(a.ptr, &a.sz, mask);
  vec b = newVec();
  copyVec(b, a);
  m = a.sz;
  for(int c=0; c<n; c++){
    bool ok = false;
    for(int r=c; r<m; r++){
      if(a.ptr[r] & (1 << c)){
        swap(a.ptr[r], a.ptr[c]);
        swap(b.ptr[r], b.ptr[c]);
        for(int i=c+1; i<m; i++)
          if(a.ptr[i] & (1 << c))
             a.ptr[i] ^= a.ptr[c];
        ok = true;
        break;
      }
    }
    if(!ok){
      puts("impossible");
      return 0;
    }
  }
  vec gray = newVec();
  gray.ptr = pushback(gray.ptr, &gray.sz, 0);
  for(int k=0; k<n; k++)
    for(int i=(1 << k)-1; i>=0; i--)
      gray.ptr = pushback(gray.ptr, &gray.sz, gray.ptr[i] ^ b.ptr[k]);
  for(int z=0;z<gray.sz;z++){int x = gray.ptr[z];
    for(int i=0; i<n; i++)
      putchar('0' + !!(x & (1 << i)));
    putchar('\n');
  }
  return 0;
}
