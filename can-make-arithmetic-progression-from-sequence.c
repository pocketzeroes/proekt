int cmp(const void*a, const void*b){ return(*(int*)a-*(int*)b);}

bool canMakeArithmeticProgression(int*as, int asSz){
  qsort(as, asSz, sizeof(int), cmp);
  int d=as[1]-as[0];
  for(int i=0;i+1<asSz;i++)
    if(as[i+1]-as[i]!=d)
      return false;
  return true;
}
