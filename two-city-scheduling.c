typedef int* intp;
int cmp(const void*pa, const void*pb){
  intp*ptra=(intp*)pa;
  intp*ptrb=(intp*)pb;
  int*a = *ptra;
  int*b = *ptrb;
  return((a[0]-a[1])-(b[0]-b[1]));
}
int twoCitySchedCost(int**costs, int costsSz, int*costs0sz){
  int res = 0;
  int costsLength = costsSz/2;
  qsort(costs, costsSz, sizeof(int*), cmp);
  for(int i=0; i<costsLength; i++){
    res += (costs[i][0] + costs[i + costsLength][1]);
  }
  return res;
}
