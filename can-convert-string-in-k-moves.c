int moddw_L(int*a, int b){
  (*a) %= b;
  if(*a < 0){
    *a += b;
  }
  return *a;
}
bool canConvertString(char*s, char*t, int k){
  int i;
  int cnt[26] = {};
  int us;
  if(strlen(s) != strlen(t)){
    return false;
  }
  for(i=(0);s[i];i++){
    int ts=t[i]-s[i];
    cnt[(moddw_L(&ts,26))]++;
  }
  for(i=(1);i<(26);i++){
    us = (k + 26 - i) / 26;
    if(us < cnt[i]){
      return false;
    }
  }
  return true;
}
