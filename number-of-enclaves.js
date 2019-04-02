function run(A, i, j, h, w){
  A[i][j] = 0;
  let dy4 = [ -1, 0, 1, 0];
  let dx4 = [ 0, 1, 0, -1];
  for(let d=0;d<4;++d){
    let di = dy4[d] + i;
    let dj = dx4[d] + j;
    if(!(0<=di && di<h) || !(0<=dj && dj<w))
      continue;
    if(A[di][dj] == 0)
      continue;
    A[di][dj] = 0;
    run(A, di, dj, h, w);
  }
}
function numEnclaves(A){
  let h = A.length,
      w = A[0].length;
  for(let i=0;i<h;++i){
    if(A[i][0] == 1) 
      run(A, i, 0, h, w);
    if(A[i][w-1] == 1)
      run(A, i, w-1, h, w);
  }
  for(let j=0;j<w;++j) {
    if(A[0][j] == 1)
      run(A, 0, j, h, w);
    if(A[h-1][j] == 1)
      run(A, h-1, j, h, w);
  }
  let ans = 0;
  for(let i=0;i<h;++i)
    for(let j=0;j<w;++j)
      ans += A[i][j];
  return ans;
}
