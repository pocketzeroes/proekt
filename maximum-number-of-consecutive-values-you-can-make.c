int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}
int getMaximumConsecutive(int*coins, int coinsSz){
  qsort(coins, coinsSz, sizeof(int), cmp);
  int re = 0;
  for(int z=0;z<coinsSz;z++){int c = coins[z];
    if(c <= re + 1)
      re += c;
  }
  return re+1;
}
