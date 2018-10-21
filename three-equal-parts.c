int*threeEqualParts(int*A, int Asz, int*rsz){
 *rsz = 2;
  int*rv = calloc(2, sizeof(int));
  int n = Asz;
  int total = 0;
  for(int z=0;z<Asz;z++){int a = A[z];
    total += a;
  }
  if(total % 3 != 0){
    rv[0] = rv[1] = -1;
    return rv;
  }
  if(total == 0){
    rv[0] = 0;
    rv[1] = 2;
    return rv;
  }
  int goal = total / 3;
  int j = n-1;
  for(; j >= 0; --j ){
    goal -= A[j];
    if(goal == 0)
      break;
  }
  int i = 0;
  for(; i < n; ++i )
    if (A[i] == 1)
      break;
  int ii = i, jj = j;
  for(; jj < n; ++jj, ++ii )
    if(A[ii] != A[jj]){
      rv[0] = rv[1] = -1;
      return rv;
    }
  rv[0] = ii-1;
  rv[1] = j;
  jj = j;
  while(A[ii] == 0)
    ++ii;
  for(; jj < n; ++jj, ++ii )
    if (A[ii] != A[jj]){
      rv[0] = rv[1] = -1;
      return rv;
    }
  rv[1] = ii;
  return rv;
}
