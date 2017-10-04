#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Pos_s{
    int init;
    int fin;
}Pos;


int main(){
    int penalty, i, n;
    Pos pos[105], temp;
    scanf("%d", &n);
    for(i = 1; i <= n; i++){
        pos[i].init = i;
        scanf("%d", &penalty);
        pos[i].fin = i + penalty;
    }
    for (i = 1; i <= n; i++){
        for (int j = 1; j < i; j++){
            if (pos[i].fin <= pos[j].fin){
                temp = pos[i];
                pos[i] = pos[j];
                pos[j] = temp;
            }
        }
    }
    for (i = 1; i <= n; i++){
        printf("%d ", pos[i].init);
    }
}
