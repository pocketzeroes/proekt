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

char*feld[2][50];
int W,H,N,S[2];

int checkWin(){
    int res = 3;
    for (int p = (0); p < (2); p++)
        if(S[p])
            res &= 1<<p;
    return res;
}
int main(){
    int tc, win, x, y;
    scanf("%d", &tc);
    while(tc--){
        scanf("%d %d %d", &W, &H, &N);
        for (int p = (0); p < (2); p++)
            for(int i = (H)-1; i >= (0); i--)
                feld[p][i]=getstr();
        S[0] = S[1] = 0;
        for (int p = (0); p < (2); p++)
            for (int h = (0); h < (H); h++)
                for (int w = (0); w < (W); w++)
                    if(feld[p][h][w] == '#')
                        ++S[p];
        win = checkWin();
        while(N>0 && win == 0){
            for (int p = (0); p < (2); p++){
                while(N-->0){
                    scanf("%d %d", &x, &y);
                    if(feld[p^1][y][x] == '#'){
                       feld[p^1][y][x] =  ' ';
                        if(0==--S[p^1])
                            break;
                    }
                    else
                        break;
                }
            }
            if(win == 0)
                win = checkWin();
        }
        while(N-->0)
            scanf("%d %d", &x, &y);
        if(win == 0 || win == 3)
            puts("draw");
        else if(win == 1)
            puts("player one wins");
        else
            puts("player two wins");
    }
    return 0;
}
