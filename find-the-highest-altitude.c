int chmax(int*a, int b){
  if(*a<b)
    *a=b;
  return *a;
}
int largestAltitude(int*gain, int gainSz){
  int i;
  int res = 0;
  int now = 0;
  for(i=(0);i<gainSz;i++){
    now += gain[i];
    chmax(&res, now);
  }
  return res;
}
