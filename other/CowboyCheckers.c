#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int mills[8][3][2]={{{0,0},{0,3},{0,6}},
                    {{1,1},{1,3},{1,5}},
                    {{2,2},{2,3},{2,4}},
                    {{3,0},{3,1},{3,2}},
                    {{3,4},{3,5},{3,6}},
                    {{4,2},{4,3},{4,4}},
                    {{5,1},{5,3},{5,5}},
                    {{6,0},{6,3},{6,6}}};
char board[7][7];

int count(){
    int count = 0;
    for(int i=0;i<8;i++){
#define mill mills[i]
        int A = 0,
            B = 0;
        for(int j=0;j<3;j++){int*arr = mill[j];
            if(board[arr[0]][arr[1]] == 'W') A++;
            if(board[arr[1]][arr[0]] == 'W') B++;
        }
        if(A == 3) count++;
        if(B == 3) count++;
#undef mill
    }
    return count;
}
int main(){
    for(int i=0; i<7; i++){
        for(int j=0; j<7; j++){
            board[i][j] = getchar();
        }
        getchar();
    }
    int c = count();
    for(int i=0;i<8;i++){
#define mill mills[i]
        int A = 0, B = 0;
        for(int j=0;j<3;j++){int*arr = mill[j];
            if(board[arr[0]][arr[1]] == 'W') A++;
            if(board[arr[1]][arr[0]] == 'W') B++;
        }
        if(A == 3){
            for(int j=0;j<3;j++){int*arr = mill[j];
                int x = arr[0],
                    y = arr[1];
                if(y != 3){
                    if(x <= 3){
                        int nx = x + abs(y - 3);
                        int ny = y;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                    if(x >= 3){
                        int nx = x - abs(y - 3);
                        int ny = y;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
                else{
                    if(x != 2 && x != 6){
                        int nx = x + 1;
                        int ny = y;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y]   = 'W';
                        }
                    }
                    if(x != 0 && x != 4){
                        int nx = x - 1;
                        int ny = y;
                        if( board[nx][ny] == '.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
                if(x != 3){
                    if(y <= 3){
                        int nx = x;
                        int ny = y + abs(x - 3);
                        if( board[nx][ny] == '.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                    if(y >= 3){
                        int nx = x;
                        int ny = y - abs(x - 3);
                        if( board[nx][ny] == '.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
                else{
                    if(y != 2 && y != 6){
                        int nx = x;
                        int ny = y + 1;
                        if( board[nx][ny] == '.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                    if(y != 0 && y != 4){
                        int nx = x;
                        int ny = y - 1;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
            }
        }
        if(B == 3){
            for(int j=0;j<3;j++){int*arr = mill[j];
                int x = arr[1],
                    y = arr[0];
                if(y != 3){
                    if(x <= 3){
                        int nx = x + abs(y - 3);
                        int ny = y;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                    if(x >= 3){
                        int nx = x - abs(y - 3);
                        int ny = y;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
                else{
                    if(x != 2 && x != 6){
                        int nx = x + 1;
                        int ny = y;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                    if(x != 0 && x != 4){
                        int nx = x - 1;
                        int ny = y;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
                if(x != 3){
                    if(y <= 3){
                        int nx = x;
                        int ny = y + abs(x - 3);
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                    if(y >= 3){
                        int nx = x;
                        int ny = y - abs(x - 3);
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
                else{
                    if(y != 2 && y != 6){
                        int nx = x;
                        int ny = y + 1;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                    if(y != 0 && y != 4){
                        int nx = x;
                        int ny = y - 1;
                        if( board[nx][ny] =='.'){
                            board[ x][ y] = '.';
                            board[nx][ny] = 'W';
                            if(count() == c){
                                puts("double mill");
                                exit(0);
                            }
                            board[nx][ny] = '.';
                            board[ x][ y] = 'W';
                        }
                    }
                }
            }
        }
#undef mill
    }
    puts("no double mill");
    return 0;
}
