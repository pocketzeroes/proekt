#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char board[9][9];
const int offset = 2;

bool getInput(){
    for (int i=(0); i < ((int)5); i++){
        for (int j=(0); j < ((int)5); j++){
            scanf("%c", &board[offset+i][offset+j]);
        }
        scanf(" ");
    }
    return true;
}
bool check_knight(int row, int col){
    return (
        (board[row+offset-2][col+offset-1] == '.') &&
        (board[row+offset-2][col+offset+1] == '.') &&
        (board[row+offset-1][col+offset-2] == '.') &&
        (board[row+offset+1][col+offset-2] == '.') &&
        (board[row+offset+2][col+offset-1] == '.') &&
        (board[row+offset+2][col+offset+1] == '.') &&
        (board[row+offset-1][col+offset+2] == '.') &&
        (board[row+offset+1][col+offset+2] == '.'));
}
void process(){
    bool v = true;
    int nk = 0;
    for (int i=(0); i < ((int)5); i++){
        for (int j=(0); j < ((int)5); j++){
            if (board[offset+i][offset+j] == 'k'){
                if (v)
                    v = check_knight(i, j);
                nk++;
            }
        }
    }
    printf("%svalid\n", nk == 9 ? (v ? "" : "in") : "in");
}
int main(){
    memset(board, '.', sizeof(board[0][0])*9*9);
    getInput();
    process();
    return 0;
}
