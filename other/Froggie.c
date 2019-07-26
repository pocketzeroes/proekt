#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

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

int sit[15][5];
pair pos;   
pair dir[4];

int main(){
    memset(sit, 0, sizeof(sit));
    int m, n;
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++){
        for (int j = 0; j < 3; j++){
            scanf("%d", &sit[i][j]);
        }
        if (i % 2 != 0){
            sit[i][0] = n - sit[i][0] - 1;
        }
    }
    pos.first = m;
    scanf("%d", &pos.second);
    char*s=getstr();
    int len = strlen(s);
    dir[0].first =-1, dir[0].second = 0;
    dir[1].first = 1, dir[1].second = 0;
    dir[2].first = 0, dir[2].second =-1;
    dir[3].first = 0, dir[3].second = 1;
    for (int i = 0; i < len; i++){
        switch (s[i]){
            case 'U':pos.first += dir[0].first, pos.second += dir[0].second; break;
            case 'D':pos.first += dir[1].first, pos.second += dir[1].second; break;
            case 'L':pos.first += dir[2].first, pos.second += dir[2].second; break;
            case 'R':pos.first += dir[3].first, pos.second += dir[3].second; break;
        }
        if (pos.first == -1){
            printf("safe\n");
            return 0;
        }
        if (pos.first >= m)
            continue;
        if (pos.second < 0 || pos.second >= n)
            return -1;
        int step;
        if (pos.first % 2 == 0){
            step = sit[pos.first][0] + sit[pos.first][2] * (i + 1);
        }
        else{
            step = sit[pos.first][0] - sit[pos.first][2] * (i + 1);
        }
        if ((step - pos.second) % sit[pos.first][1] == 0){
            printf("squish\n");
            return 0;
        }
    }
    printf("squish\n");
    return 0;
}
