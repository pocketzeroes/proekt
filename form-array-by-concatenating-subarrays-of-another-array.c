typedef long long ll;

bool canChoose(int**groups, int groupsSz, int*groups0sz, int*nums, int numsSz){
  int now=0;
  for(int z=0;z<groupsSz;z++){int*g=groups[z];
    int gSz=groups0sz[z];
    int ok=0;
    int i;
    while(now+gSz<=numsSz){
      for(i=0;i<gSz;i++)if(nums[now+i]!=g[i])break;
      if(i==gSz){
        ok=1;
        now+=gSz;
        break;
      }
      now++;
    }
    if(ok==0)
      return 0;
  }
  return 1;
}
