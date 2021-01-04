void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int*findBall(int**grid, int gridSz, int*grid0sz, int*rsz){
  int r = gridSz;
  int c = grid0sz[0];
  int*ret=calloc(c, sizeof(int));
  fill(ret, c, -1);
  for(int j=0; j<c; j++){
    int curri = 0;
    int currj = j;
    bool done = false;
    while(curri < r&&!done){
      int ni = curri+1;
      int nj = currj + grid[curri][currj];
      if(grid[curri][currj] == 1 && (currj+1 == c || grid[curri][currj+1] == -1)){
        done = true;
        break;
      }
      if(grid[curri][currj] == -1 && (currj == 0 || grid[curri][currj-1] == 1)){
        done = true;
        break;
      }
      curri = ni;
      currj = nj;
    }
    if(!done)
      ret[j] = currj;
  }
 *rsz=c;
  return ret;
}
