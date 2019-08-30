#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
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
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
#define pb(zpv, zvv) zpv.ptr = pushback(zpv.ptr, &zpv.sz, zvv)
typedef struct{
  int first;
  int second;
}pair;
pair newPair(int a, int b){
  pair rez;
  rez.first =a;
  rez.second=b;
  return rez;
}
int cmpP(pair a, pair b){
  if(a.first  != b.first) return(a.first  < b.first )?-1:1;
  if(a.second != b.second)return(a.second < b.second)?-1:1;
  return 0;
}


enum{INTMAX=70000};
int bx = -1, bxs = -1, by = -1, bys = -1;
int best_sq = 1;

void rem(vec*height, vec*starts, int h, int j, int i, int*start){
#define hback height->ptr[height->sz-1]
#define sback starts->ptr[starts->sz-1]
  while(height->sz && hback >= h){
    int sq = fmin(hback, (j - sback));
    if(sq > best_sq){
      by = sback;
      bys = j - sback;
      bx = i;
      bxs = hback;
    }
    best_sq = fmax(best_sq , sq);
    height->sz--;
   *start = sback;
    starts->sz--;
  }
}
int main(){
  int x, y;
  scanf("%d %d", &x, &y);
  while(x != 0 && y != 0){
    bx = -1, bxs = -1, by = -1, bys = -1;
    best_sq = 1;
    int table[x][y];
    for(int i = 0; i < x; i++)
      for(int j = 0; j < y; j++)
        scanf("%d", &table[i][j]);
    int*heights[x];
    heights[x-1]=calloc(y,sizeof(int)); fill(heights[x-1], y, 1);
    if(x > 2)
      heights[x-2] = calloc(y,sizeof(int)); fill(heights[x-2], y, 2);
    for(int i = x - 3; i >= 0; i--){
      heights[i] = calloc(y,sizeof(int));fill(heights[i], y, 2);
      for(int j = 0; j < y; j++){
        if(table[i+2][j] - table[i+1][j] == table[i+1][j] - table[i][j])
          heights[i][j] = heights[i+1][j] + 1;
      }
    }
    for(int i = 1; i < x; i++){
      vec starts = newVec();
      vec height = newVec();
      pair ctype = newPair(INTMAX, INTMAX);
      for(int j = 1; j < y; j++){
        int bt  = table[i-1][j  ] - table[i  ][j  ];
        int sbt = table[i-1][j-1] - table[i  ][j-1];
        int at  = table[i  ][j-1] - table[i  ][j  ];
        int sat = table[i-1][j-1] - table[i-1][j  ];
        pair type = newPair(at, bt);
        int start = j-1, fs = j-1;
        if((abs(at) != abs(bt) && at != 0 && bt != 0) ||  at != sat || bt != sbt){
          type = newPair(INTMAX, INTMAX);
          start = j;
        }
        int h = fmin(heights[i-1][j - 1], heights[i-1][j]);
        if(cmpP(type, ctype)==0 &&
           cmpP(type, newPair(INTMAX, INTMAX))!=0)
           rem(&height, &starts, h, j, i-1, &start);
        else
          rem(&height, &starts, -1, j, i-1, &fs);
        ctype = type;
        pb(starts, start);
        pb(height, h);
      }
      int start = 0;
      rem(&height, &starts, -1, y, i-1, &start);
    }
    printf("%d\n", best_sq * best_sq);
    scanf("%d %d", &x, &y);
  }
  return 0;
}
