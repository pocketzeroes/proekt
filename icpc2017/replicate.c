/* https://youtu.be/BZo23gj9ksk?t=7646 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include<stdbool.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}


enum{ N=333};
char s         [N][N];
char new_s     [N][N];
char tmp       [N][N];
char pref[2][N][2][N];
bool bad_pref  [2][N];

int main(){
  int w,h;
  scanf("%d %d", &w, &h);
  for(int i=0;i<h;i++){
    scanf("%s", s[i]);
  }
  while(true){
    int cells=0;
    for(int i=0;i<h;i++){
      for(int j=0;j<w;j++){
        cells+=(s[i][j]!='.');
      }
    }
    if(cells<=1){
      break;
    }
    for (int rot=0;rot<2;rot++){
      for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
          tmp[i][j] = s[ rot==0?i:h-i-1][j];
        }
      }
      bool fail=false;
      for(int i=0;i<=h-2;i++){
        bad_pref[rot][i]=fail;
        if(fail){
          continue;
        }
        for(int j=0;j<w;j++){
          pref[rot][i][0][j] = tmp[i  ][j];
          pref[rot][i][1][j] = tmp[i+1][j];
        }
        if(i==h-2)
          break;
        for(int j=0;j<w-2;j++){
          if(tmp[i][j]!='.'){
            for(int dx=0;dx<3;dx++){
              for(int dy=0;dy<3;dy++){
                tmp[i+dx][j+dy]='.'+'#'-tmp[i+dx][j+dy];
              }
            }
          }
        }
        if(tmp[i][w-2]!='.' ||tmp[i][w-1]!='.'){
          fail=true;
        }
      }      
    }
    bool found=false;
    for(int up=0;up<=h-2;up++){
      int down=h-2-up;
      if(bad_pref[0][up]||bad_pref[1][down]){
        continue;
      }
      int sum=0;
      int xx=-1,yy=-1;
      for(int i=0;i<2;i++){
        for(int j=0;j<w;j++){
          int real=(s[up+i][j]=='.'?0:1);
          int change_up = (s[up+i][j] == pref[0][up  ][i  ][j]?0:1);
          int change_down=(s[up+i][j] == pref[1][down][1-i][j]?0:1);
          int result=(real^change_up^change_down);
          sum+=result;
          if(result){
            xx=up+i;
            yy=j;
          }
        }
      }
      if(sum<=1){
        if(xx!=-1){
          s[xx][yy]='.'+'#'-s[xx][yy];
        }
        for(int i=0;i<h-2;i++){
          for(int j=0;j<w-2;j++){
            new_s[i][j]=s[i][j];
            if(s[i][j]!='.'){
              for(int dx=0;dx<3;dx++){
                for(int dy=0;dy<3;dy++){
                  s[i+dx][j+dy]='.'+'#'-s[i+dx][j+dy];
                }
              }
            }
          }
        }
        for(int i=0;i<h;i++){
          for(int j=0;j<w;j++){
            if(i>=h-2 || j>= h-2){
              assert(s[i][j]=='.');
            }
          }
        }
        for(int i=0;i<h - 2;i++){
          for(int j=0;j<w - 2;j++){       
            s[i][j]=new_s[i][j];
          }
        }
        h-=2;
        w-=2;
        found=true;
        break;
      }
    }
    if(!found){
      break;
    }
  }
  int min_x=h, min_y =w;
  int max_x=-1, max_y=-1;
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      if(s[i][j]!='.'){
        min_x = min(min_x, i);
        min_y = min(min_y, j);
        max_x = max(max_x, i);
        max_y = max(max_y, j);
      }
    }
  }
  for(int i=min_x;i<=max_x;i++){
    for(int j=min_y;j<=max_y;j++){
      putchar(s[i][j]);
    }
    puts("");
  }
  return 0;
}














































