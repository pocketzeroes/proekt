#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef long long ll;
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
void tooMany(){
  puts("too many");
  exit(0);
}
#define max 1000000000000000000ll

int main(){
  int r = in_nextInt();
  int s = in_nextInt();
  int m = in_nextInt();
  int d = in_nextInt();
  int n = in_nextInt();
  int b[r+1];clr(b);
  b[0] = 1;
  for(int i=0; i<r; i++){
    b[i + 1] = in_nextInt();
  }
  int ingredients[s+m+d][20]; clr(ingredients);
  for(int i=0; i<s+m+d; i++){
    int islen=in_nextInt();
    for(int j=0; j<islen; j++){
      ingredients[i][j] = in_nextInt();
    }
  }
  bool incompatible[s+m+d][s+m+d]; clr(incompatible);
  for(int i=0; i<n; i++){
    int x = in_nextInt()-1;
    int y = in_nextInt()-1;
    incompatible[x][y] = true;
    incompatible[y][x] = true;
  }
  ll nr = 0;
  for(int x=0; x<s; x++){
    for(int y=s; y<s+m; y++){
      if(incompatible[x][y])
        continue;
      for(int z=s+m; z<s+m+d; z++){
        if(incompatible[x][z] || incompatible[y][z])
          continue;
        ll p = 1;
        bool added[r+1]; clr(added);
        for(int i=0; i<20; i++){
          if(!added[ingredients[x][i]]){
            if(b[ingredients[x][i]] > max / p + 1)
              tooMany();
            added[ingredients[x][i]] = true;
            p *= b[ingredients[x][i]];
          }
          if(!added[ingredients[y][i]]){
            if(b[ingredients[y][i]] > max / p + 1)
              tooMany();
            added[ingredients[y][i]] = true;
            p *= b[ingredients[y][i]];
          }
          if(!added[ingredients[z][i]]) {
            if(b[ingredients[z][i]] > max / p + 1)
              tooMany();
            added[ingredients[z][i]] = true;
            p *= b[ingredients[z][i]];
          }
        }
        nr += p;
        if(nr > max)
          tooMany();
      }
    }
  }
  printf("%lld\n", nr);
  return 0;
}
