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

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  int*ptr;
  int sz;
}vec;
vec newVec() {
  vec rez;// = malloc(sizeof(vec));
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
//////////////////////////////

enum{ MIN_W    = 2            };
enum{ MIN_H    = 1            };
enum{ MAX_W    = 50           };
enum{ MAX_H    = 50           };
enum{ MAX_AREA = MAX_W * MAX_H};

int H,W;
int grid     [MAX_H][MAX_W];
vec neigh    [MAX_AREA];
int exits    [2];
int discovery[MAX_AREA];
int finish   [MAX_AREA];
int timestamp;


void reset() {
    timestamp = 0;
    for (int k=0; k < W*H; k++) {
        discovery[k] = finish[k] = -1;
    }
}
void dfs(int u) {
    discovery[u] = timestamp++;
    for (int j=0; j < neigh[u].sz; ++j){
        int v = neigh[u].ptr[j];
        if (discovery[v] == -1)
            dfs(v);
    }
    finish[u] = timestamp++;
}
void recordExit(int*numTerm, int r, int c) {
    (*numTerm)++;
    if(*numTerm <= 2)
      exits[*numTerm-1] = r*W + c;
}
int main(){
    while (1){
        scanf("%d %d", &H, &W);
        if (W == 0)
            break;
        for (int r=0; r < H; r++) {
            char*temp=getstr();
            for (int c=0; c < W; c++) {
                if (temp[c] >= '0' && temp[c] <= '9')
                    grid[r][c] = temp[c] - '0';
                else if (temp[c] >= 'A' && temp[c] <= 'F')
                    grid[r][c] = 10 + temp[c] - 'A';
                else
                    puts("ERROR: Illegal digit");
            }
        }
        bool consistent = true;
        for (int r=0; r < H; r++) {
            for (int c=0; c < W; c++) {
                if (r > 0)
                    if (((grid[r][c] & 8) == 0) != ((grid[r-1][c] & 2) == 0))
                        consistent = false;
                if (c > 0)
                    if (((grid[r][c] & 1) == 0) != ((grid[r][c-1] & 4) == 0))
                        consistent = false;
            }
        }
        if (!consistent){
            puts("ERROR: Inconsistent hex encoding");
            continue;
        }
        int numTerm = 0;
        for (int r=0; r < H; r++) {
            if ((grid[r][0] & 1) == 0)
                recordExit(&numTerm,r,0);
            if ((grid[r][W-1] & 4) == 0)
                recordExit(&numTerm,r,W-1);
        }
        for (int c=0; c < W; c++) {
            if ((grid[0][c] & 8) == 0)
                recordExit(&numTerm,0,c);
            if ((grid[H-1][c] & 2) == 0)
                recordExit(&numTerm,H-1,c);
        }
        if (numTerm != 2 || exits[0] == exits[1]) {
            puts("ERROR: invalid terminals");
            continue;
        }
        for (int k=0; k < W*H; k++)
            neigh[k].sz=0;
        for (int r=0; r < H; r++) {
            for (int c=0; c < W; c++) {
                int k = r*W + c;
                if (r > 0   && ((grid[r][c] & 8) == 0)) neigh[k].ptr = pushback(neigh[k].ptr, &neigh[k].sz, (r-1)*W +c);
                if (c < W-1 && ((grid[r][c] & 4) == 0)) neigh[k].ptr = pushback(neigh[k].ptr, &neigh[k].sz, r*W + c+1 );
                if (r < H-1 && ((grid[r][c] & 2) == 0)) neigh[k].ptr = pushback(neigh[k].ptr, &neigh[k].sz, (r+1)*W +c);
                if (c > 0   && ((grid[r][c] & 1) == 0)) neigh[k].ptr = pushback(neigh[k].ptr, &neigh[k].sz, r*W + c-1 );
            }
        }
        reset();
        dfs(exits[0]);
        if (discovery[exits[1]] == -1) {
            puts("NO SOLUTION");
            continue;
        }
        bool connected = true;
        for (int k=0; k < W*H; k++)
            if (discovery[k] == -1) {
                connected = false;
                break;
            }
        if (!connected) {
            puts("UNREACHABLE CELL");
            continue;
        }
        int numEdges = 0;
        for (int k=0; k < W*H; k++)
            numEdges += neigh[k].sz;
        numEdges /= 2;
        if (numEdges != W*H - 1) {
            puts("MULTIPLE PATHS");
            continue;
        }
        puts("MAZE OK");
    }
}
