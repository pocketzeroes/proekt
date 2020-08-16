int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}

int maxDistance(int*position, int positionSz, int m) {
    qsort(position, positionSz, sizeof(int), cmp);
    int lhs = 1;
    int rhs = (int)1e9;
    while(lhs < rhs){
      int mid = (lhs+rhs+1)/2;
      int last = -1e9;
      int placed = 0;
      for(int z=0;z<positionSz;z++){int out=position[z];
        if(out - last >= mid){
          placed++;
          last = out;
        }
      }
      if(placed >= m)
          lhs = mid;
      else
          rhs = mid-1;
    }
    return lhs;
}
