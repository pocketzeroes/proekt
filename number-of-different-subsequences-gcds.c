int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
enum{MAX =(int) 2e5 + 1};
bool cnt[MAX];

int countDifferentSubsequenceGCDs(int*nums, int numsSz){
  memset(cnt, 0, sizeof(cnt));
  for(int z=0;z<numsSz;z++){int x = nums[z];
    cnt[x] = true;
  }
  int ret = 0;
  for(int x=1; x<MAX; x++){
    int g = 0;
    for(int y=x; y<MAX; y+=x)
      if(cnt[y])
        g = gcd(g, y);
    if(g == x)
      ret++;
  }
  return ret;
}
