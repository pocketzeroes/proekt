#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef struct Cell{
    bool isSingle;
    int  first;
    int  second;
}Cell;

int parse(char c){
    if (c == '-') 
        return 0;
    else
        return c - '0';
}
Cell newCell(char*token){
    Cell rez;
    if(strlen(token) > 1 && token[1] == '/'){
        rez.isSingle = false;
        rez.first    = parse(token[0]);
        rez.second   = parse(token[2]);
    } 
    else{
        rez.isSingle = true;
        rez.first    = parse(token[0]);
    }
    return rez;
}
char*toString(Cell*c){
    char*ch = NULL;
    if(c->isSingle)
        asprintf(&ch, "%d", c->first);
    else
        asprintf(&ch, "%d/%d", c->first, c->second);
    return ch;
}

////////////////
enum{ SIZE = 6};
Cell board[SIZE][SIZE];
bool  solved;
int   rowMask [SIZE];
int   colMask [SIZE];
int   cellMask[SIZE];

void print(){
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%s", toString(&board[i][j]));
            if(j < 6)
                printf(" ");
        }
        puts("");
    }
}
int getCell(int i, int j){
    return 2 * (i / 2) + (j / 3);
}
void dfs(int r, int c){
    if (solved)
        return;
    if (c == SIZE){
        dfs(r + 1, 0);
        return;
    }
    if (r == SIZE){
        solved = true;
        print();
        return;
    }
    int cell = getCell(r, c);
    int mask = rowMask[r] | colMask[c] | cellMask[cell];
    if (!board[r][c].isSingle && board[r][c].first == 0 && board[r][c].second == 0){
        for (int i = 1; i <= 9; i++){
            int bit = (1 << i);
            if ((mask & bit) != 0)
                continue;
            rowMask[r]     ^= bit;
            colMask[c]     ^= bit;
            cellMask[cell] ^= bit;
            board[r][c].first = i;
            for (int j = i + 1; j <= 9; ++j) {
                int bit2 = (1 << j);
                if ((mask & bit2) != 0)
                    continue;
                rowMask[r] ^= bit2;
                colMask[c] ^= bit2;
                cellMask[cell] ^= bit2;
                board[r][c].second = j;
                dfs(r, c + 1);
                rowMask[r] ^= bit2;
                colMask[c] ^= bit2;
                cellMask[cell] ^= bit2;
                board[r][c].second = 0;
            }
            board[r][c].first = 0;
            rowMask[r] ^= bit;
            colMask[c] ^= bit;
            cellMask[cell] ^= bit;
        }
    } 
    else if (board[r][c].first == 0) {
        for (int i = 1; i <= 9; i++) {
            int bit = (1 << i);
            if ((mask & bit) != 0)
                continue;
            if (!board[r][c].isSingle && i > board[r][c].second)
                continue;
            rowMask[r]     ^= bit;
            colMask[c]     ^= bit;
            cellMask[cell] ^= bit;
            board[r][c].first = i;
            dfs(r, c + 1);
            board[r][c].first = 0;
            rowMask[r] ^= bit;
            colMask[c] ^= bit;
            cellMask[cell] ^= bit;
        }
    }
    else if (!board[r][c].isSingle && board[r][c].second == 0) {
        for (int i = board[r][c].first + 1; i <= 9; i++) {
            int bit = (1 << i);
            if ((mask & bit) != 0)
                continue;
            rowMask[r] ^= bit;
            colMask[c] ^= bit;
            cellMask[cell] ^= bit;
            board[r][c].second = i;
            dfs(r, c + 1);
            board[r][c].second = 0;
            rowMask[r] ^= bit;
            colMask[c] ^= bit;
            cellMask[cell] ^= bit;
        }
    } 
    else
        dfs(r, c + 1);
}
char buff[256];
int main(){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            scanf("%s", &buff);
            board[i][j] = newCell(buff);
            int val = board[i][j].first;
            if (val != 0){
                rowMask[i] |= (1 << val);
                colMask[j] |= (1 << val);
                cellMask[getCell(i, j)] = (1 << val);
            }
            if (!board[i][j].isSingle && board[i][j].second != 0){
                val = board[i][j].second;
                rowMask[i] |= (1 << val);
                colMask[j] |= (1 << val);
                cellMask[getCell(i, j)] = (1 << val);
            }
        }
    }
    solved = false;
    dfs(0, 0);
}



