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

int x, y;
int n;
char*s[100];

int main(){
    scanf("%d%d", &x, &y);
    scanf("%d", &n);
    for (int i = 0; i < n; ++i)
        s[i]=getstr();
    int best_i = 1 << 20;
    char*best_ss = strdup("");
    for(int k = 0; k < 3; ++k){
        char*s_replace;
        if      (k == 0) s_replace = "Forward";
        else if (k == 1) s_replace = "Left"   ;
        else if (k == 2) s_replace = "Right"  ;
        for (int i = 0; i < n; ++i){
            int xx = 0;
            int yy = 0;
            int dx = 0;
            int dy = 1;
            for(int j = 0; j < n; ++j){
                char*ss = s[j];
                if(i == j)
                    ss = s_replace;
                if (ss[0] == 'F') {
                    xx += dx;
                    yy += dy;
                } 
                else if (ss[0] == 'L') {
                    int dx1 = -dy;
                    int dy1 = dx;
                    dx = dx1;
                    dy = dy1;
                } 
                else {
                    int dx1 = dy;
                    int dy1 = -dx;
                    dx = dx1;
                    dy = dy1;
                }
            }
            if (xx == x && yy == y) {
                if (i < best_i) {
                    best_i = i;
                    best_ss = s_replace;
                }
                break;
            }
        }
    }
    printf("%d %s\n", best_i+1, best_ss);
    return 0;
}
