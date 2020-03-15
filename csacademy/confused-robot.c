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
  scanf("%s", buff+1);
  return strdup(buff);
}

typedef struct{
  int first, second;
}pair;
pair newpair(int a, int b){
  return(pair){a,b};
}
////////////////////

int dx[300];
int dy[300];
int n,m,q;
char*s;
char*v[505];
pair smecherie[31][505][505];

pair brute(pair pos, int pref){
   for(int i=0; i<pref; i++){
      pair nxt =(pair){pos.first + dx[s[i]],pos.second + dy[s[i]]};
      if(nxt.first > 0 && nxt.first <= n && nxt.second > 0 && nxt.second <= m && v[nxt.first][nxt.second] != '#'){
         pos = nxt;
      }
   }
   return pos;
}
int main(){
   buff[0] = ' ';
   dx['U'] =-1;dy['U'] = 0;
   dx['L'] = 0;dy['L'] =-1;
   dx['D'] = 1;dy['D'] = 0;
   dx['R'] = 0;dy['R'] = 1;
   scanf("%d %d %d", &n, &m, &q);
   for(int i=1; i<=n; i++){
      v[i] = getstr();
//    v[i] = prepend " " + v[i];
   }
   s=getstr();
   s++;
   int slen=strlen(s);
   for(int i=1; i<=n; i++){
      for(int j=1; j<=m; j++){
         smecherie[0][i][j] = brute((pair){i,j},slen);
      }
   }
   for(int h=1; h<=30; h++){
      for(int i=1; i<=n; i++){
         for(int j=1; j<=m; j++){
            pair tmp = smecherie[h - 1][i][j];
            smecherie[h][i][j] = smecherie[h - 1][tmp.first][tmp.second];
         }
      }
   }
   while(q--){
      int x, y, k;
      scanf("%d %d %d", &x, &y, &k);
      int tmp = k / slen;
      k %= slen;
      for(int h = 30; h >= 0; h--){
         if(tmp & (1 << h)){
            pair a = smecherie[h][x][y];
            x = a.first;
            y = a.second;
         }
      }
      pair a = brute((pair){x,y}, k);
      printf("%d %d\n", a.first, a.second);
   }
   return 0;
}
