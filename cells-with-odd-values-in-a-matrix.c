#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int oddCells(int n, int m, int**ind, int indSz, int*ind0sz){
    int cells[n][m]; clr(cells);
    for(int z=0;z<indSz;z++){int*id = ind[z];
        for(int r = 0; r < n; r++)
            cells[r][id[1]]++;
        for(int c = 0; c < m; c++)
            cells[id[0]][c]++;
    }
    int odd = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            odd += cells[i][j] % 2;
    return odd;
}
