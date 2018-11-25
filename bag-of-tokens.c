int max(int a,int b){return a>b?a:b;}
int cmp(const void * a, const void * b){ return ( *(int*)a - *(int*)b );}

int bagOfTokensScore(int* tokens, int tokensSz, int P){
  if(tokensSz == 1){
    return P >= tokens[0] ? 1 : 0;
  }
  qsort(tokens, tokensSz, sizeof(int), cmp);
  int n = tokensSz, ans = 0;
  for(int i=(0); i<(n/2); i++) {
    int p = P, t = 0;
    for(int j=(0); j<(i); j++) {
      if (p < tokens[j]) 
        break;
      p -= tokens[j];
      p += tokens[n - 1 - j];
      t++;
    }
    int sol = 0;
    for(int j=(t); j<(n-t); j++) {
      if (p >= tokens[j]) {
        p -= tokens[j];
        sol++;
      }
      else
        break;
    }
    ans = max(ans, sol);
  }
  return ans;
}
