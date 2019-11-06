#pragma GCC optimize "-O3"
#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  free(a);
  return ptr;
}
char buff[100000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ MAX_WIDTH  = 36};
enum{ MAX_HEIGHT = 20};
int H,W;
char*original[MAX_HEIGHT+2];
int grid[MAX_HEIGHT+2][MAX_WIDTH+2];
int cycle[16];
bool isLegal[1<<12];
int delta[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

#define UNKNOWN 0
#define BLACK 1
#define WHITE 2
#define NW 3
#define NE 4
#define SE 5
#define SW 6

char*string(int sz, char ch){
  char space[sz+1]; memset(space, ch , sizeof(space)); space[sz]='\0';
  return strdup(space);
}

int getColor(int shape, int k) {
    if (shape < NW)
        return shape;
    else
        return 1 + (k+15-2*shape)%8/4;
}
int makeQuad(int r, int c) {
    return grid[r][c] + grid[r][c+1] * 8 + grid[r+1][c+1] * 64 + grid[r+1][c] * 512;
}


bool isQuadLegal(int q) {
    cycle[0] = getColor(q % 8, 5);
    cycle[1] = getColor(q % 8, 4);
    cycle[2] = getColor((q >> 3) % 8, 7);
    cycle[3] = getColor((q >> 3) % 8, 6);
    cycle[4] = getColor((q >> 6) % 8, 1);
    cycle[5] = getColor((q >> 6) % 8, 0);
    cycle[6] = getColor((q >> 9) % 8, 3);
    cycle[7] = getColor((q >> 9) % 8, 2);
    for (int j=8; j<16; j++)
        cycle[j] = cycle[j-8];
    bool active = false;
    int wCount = 0;
    for (int j=0; j<16; j++) {
        switch (cycle[j]) {
          case BLACK:
            if (active && (wCount % 2 == 1 || wCount == 6))
                return false;
            active=true;
            wCount=0;
            break;
          case WHITE:
            wCount++;
            break;
          case UNKNOWN:
            active=false;
            break;
        }
    }
    return true;
}
void precomputeLegalQuads() {
    for (int q=0; q < (1<<12); q++) {
        isLegal[q] = isQuadLegal(q);
    }
}
int numTriangles() {
    int count=0;
    for (int r=1; r <= H; r++)
        for (int c=1; c <= W; c++) {
            if (grid[r][c] >= NW)
                count += 1;
        }
    return count;
}
bool legalBlack(int r, int c) {
    if (original[r][c] == '*')
        return true;
    int tri =0, unknown = 0;
    for (int d=0; d<4; d++) {
        int shape = grid[r+delta[d][0]][c+delta[d][1]];
        if (shape == UNKNOWN)
            unknown++;
        else if (shape >= NW)
            tri++;
    }
    int need = original[r][c] - '0';
    return (tri <= need && need <= tri+unknown);
}
void solve(int r, int c) {
    if (r == H+1 && c == W+1)
        printf("%d\n", numTriangles());
    else {
        if (grid[r][c] == BLACK) {
            if (c == W+1)
                solve(r+1,1);
            else
                solve(r,c+1);
        }
        else {
            for (int shape = WHITE; shape <= SW; shape++) {
                grid[r][c] = shape;
                bool legal=true;
                legal = legal && isLegal[makeQuad(r-1,c-1)];
                legal = legal && isLegal[makeQuad(r-1,c)];
                legal = legal && isLegal[makeQuad(r,c-1)];
                legal = legal && isLegal[makeQuad(r,c)];
                for (int d=0; d<4; d++)
                    if (grid[r+delta[d][0]][c+delta[d][1]] == BLACK)
                        legal = legal && legalBlack(r+delta[d][0], c+delta[d][1]);
                if (legal)
                    solve(r,c+1);
                grid[r][c] = UNKNOWN;
            }
        }
    }
}
int main(){
    precomputeLegalQuads();
    scanf("%d %d", &W, &H);
    original[0] = string(2+W,'*');
    for(int j=1; j<=H; j++){
        original[j] = getstr();
        char*ori = strdup("*");
        ori = concats(ori, original[j]);
        ori = concatc(ori, '*');
        original[j] = ori;
    }
    original[H+1] = string(2+W,'*');
    for(int r=0; r < H+2; r++){
        for(int c=0; c < W+2; c++){
            if(original[r][c] == '.')
                grid[r][c] = UNKNOWN;
            else
                grid[r][c] = BLACK;
        }
    }
    solve(1,1);
    return 0;
}
