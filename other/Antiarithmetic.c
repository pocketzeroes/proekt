#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

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
char bs[1256];
int main(){
    while(true){
        int n; 
        scanf("%d", &n);
        if(n == 0)
            break;
        getchar();
        int a[10005];
        memset(bs, 0, sizeof(bs));
        bool aa = true;
        for (int i = 0; i < n; ++i){
            scanf("%d", &a[i]);
            if(!aa)
                continue;
            bitset_set(bs, a[i]);
            for(int j = 0, v; aa && j < i; ++j){
                if((v = a[i] + a[i] - a[j]) >= 0 && v < n && !bitset_isset(bs, v)){
                    aa = false;
                    break;
                }
            }
        }
        puts(aa ? "yes" : "no");
    }
    return 0;
}
