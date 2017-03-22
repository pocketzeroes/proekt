#include <stdio.h>

#define GRID_LENGTH 4
#define GRID_WIDTH  5

int sink(int, int);

int grid[GRID_LENGTH][GRID_WIDTH] = {
   {'1','1','1','1','0'} ,
   {'1','1','0','1','0'} ,
   {'1','1','0','0','0'} ,
   {'0','0','0','0','0'}
};
int numIslands(char** grid, int gridRowSize, int gridColSize) {
    int sink(int i, int j) {
        if (i < 0 || i == gridRowSize || j < 0 || j == gridColSize || grid[i][j] == '0')
            return 0;
        grid[i][j] = '0';
        sink(i+1, j);
        sink(i-1, j);
        sink(i, j+1);
        sink(i, j-1);
        return 1;
    }
    int islands = 0;
    for (int i=0; i< gridRowSize; i++)
        for (int j=0; j< gridColSize; j++)
            islands += sink(i, j);
    return islands;
}


int main(int argc, char**argv){

    int num = numIslands();

    printf("result is %d\n", num);

    return 0;
}

