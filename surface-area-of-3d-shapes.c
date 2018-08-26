int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

const int dir[4][2] = {{ 0,  1}, 
                       { 1,  0}, 
                       { 0, -1}, 
                       {-1,  0}};
int surfaceArea(int**grid, int gridSz, int*grid0szs){
    int ans = 0;
    if(gridSz==0||grid0szs[0]==0)
        return ans;
    int n = gridSz,
        m = grid0szs[0];
    int sum = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++) {
            sum += grid[i][j];
            ans -= max(0, 2 * (grid[i][j] - 1));
            for(int z=0; z<4; z++){int*d = dir[z];
                int i2 = i + d[0], 
                    j2 = j + d[1];
                if(i2 < 0 || i2 >= n || j2 < 0 || j2 >= m) 
                    continue;
                int t = min(grid[i][j], grid[i2][j2]);
                ans -= t;
            }
        }
    }
    ans += 6 * sum;
    return ans;
}
