
int lf[100000+1];
int rg[100000+1];
int cnt[26];

int numSplits(char*s){
  int i;
  int N = strlen(s);
  int c;
  int res = 0;
  for(i=(0);i<(N);i++){
    s[i] -= 'a';
  }
  c = 0;
  for(i=(0);i<(26);i++){
    cnt[i] = 0;
  }
  for(i=(0);i<(N);i++){
    if(cnt[s[i]]==0){
      c++;
    }
    cnt[s[i]]++;
    lf[i+1] = c;
  }
  c = 0;
  for(i=(0);i<(26);i++){
    cnt[i] = 0;
  }
  for(i=(0);i<(N);i++){
    if(cnt[s[N-1-i]]==0){
      c++;
    }
    cnt[s[N-1-i]]++;
    rg[i+1] = c;
  }
  for(i=(1);i<(N);i++){
    if(lf[i]==rg[N-i]){
      res++;
    }
  }
  return res;
}
