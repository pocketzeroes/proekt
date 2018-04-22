
int min(int a,int b){return a<b?a:b;}

int*shortestToChar(char*S, char C, int*rsz){
  int n = strlen(S);
  int*r = calloc(n, sizeof(int));
  for(int i=0;i<n;i++)
    r[i]=n;
  for(int i = (0); i < (n); i++)
    if (S[i] == C)
      r[i] = 0;
  for(int i = (1); i < (n); i++)
    r[i] = min(r[i], r[i-1]+1);
  for(int i = (n-1); --i >= (0); )
    r[i] = min(r[i], r[i+1]+1);
 *rsz=n;
  return r;
}
