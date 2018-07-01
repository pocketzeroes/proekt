bool lemonadeChange(int*bills, int billsSz){
    int cnt[5]; memset(cnt, 0, sizeof(cnt));
    for(int z=0;z<billsSz;z++){int b = bills[z];
      b /= 5;
      ++cnt[b];
      if (b == 4) {
        if (cnt[2] && cnt[1]) {
          --cnt[2];
          --cnt[1];
        }
        else if (cnt[1] >= 3)
          cnt[1] -= 3;
        else
          return false;
      } 
      else if (b == 2) {
        if (cnt[1] == 0)
          return false;
        --cnt[1];
      }
    }
    return true;
}
