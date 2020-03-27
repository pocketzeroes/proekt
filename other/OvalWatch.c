#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
int cmpP(const void*pa, const void*pb){
  pair*a = (pair*)pa;
  pair*b = (pair*)pb;
  if(a->first  != b->first) return(a->first  < b->first )?-1:1;
  if(a->second != b->second)return(a->second < b->second)?-1:1;
  return 0;
}

int k;

int binaryIndex(pair*cords, int height, int cur){
    int l = 0,
        r = k,
        index;
    bool eq    = false,
         found = false;
    while(l < r){
        int m = l + (r - l) / 2;
        if(cords[m].first == height+1){
            index = m; eq = true;
            break;
        }
        if (cords[m].first < height+1)
            l = m + 1;
        else
            r = m;
    }
    if(!eq)
        index = l;
    for(int x = index; x < k; x++){
        int line = cords[x].second;
        if(line == cur || line + 1 == cur){
            index = x; found = true;
            break;
        }
    }
    if(found)
        return index;
    else
        return k-1;
}
int main(){
    int n, i, l, h;
    scanf("%d %d", &n, &k);
    pair*cords = calloc(k, sizeof(pair));
    for(i=0; i<k; i++){
        scanf("%d %d", &h, &l);
        cords[i] = newpair(l, h);
    }
    qsort(cords, k, sizeof(pair), cmpP);
    for(i=0; i<n; i++){
        int cur    = i,
            height = 0,
            maxH = cords[k-1].first,
            index,
            line;
        while(height < maxH){
            index  = binaryIndex(cords, height, cur),
            line   = cords[index].second;
            height = cords[index].first;
            if(line == cur)
                cur++;
            else if(line + 1 == cur)
                cur--;
        }
        printf("%d ", cur);
    }
    return 0;
}
