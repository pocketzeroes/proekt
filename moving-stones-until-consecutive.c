int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
int*numMovesStones(int a, int b, int c, int*rsz){
  int d[3] = {a, b, c};
  qsort(d, 3, sizeof(int), cmp);
  int max = d[2]-d[0]-2;
  int min = 2;
  if(d[2] - d[0] == 2)
    min = 0;
  else if(d[1] - d[0] <= 2 || d[2] - d[1] <= 2)
    min = 1;
  int*rv=calloc(2, sizeof(int));
  rv[0]=min;
  rv[1]=max;
 *rsz=2;
  return rv;
}
