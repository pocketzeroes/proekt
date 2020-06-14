typedef long long ll;

int minDays(int*bloomDay, int bloomDaySz, int m, int k){
  if(m*(ll)k > bloomDaySz)
    return-1;
  int lhs = 0;
  int rhs =(int)1e9;
  while(lhs < rhs){
    int mid = (lhs+rhs)/2;
    int amt = 0;
    int cand = 0;
    for(int z=0;z<bloomDaySz;z++){int out=bloomDay[z];
      if(out <= mid)
        cand++;
      else
        cand = 0;
      if(cand == k){
        cand = 0;
        amt++;
      }
    }
    if(amt >= m)
      rhs = mid;
    else
      lhs = mid+1;
  }
  return lhs;
}
