
int*anagramMappings(int*A, int Asz, int*B, int Bsz, int*rsz){
  int N = Asz;
  int*ans = calloc(N, sizeof(int));
  for(int i=0; i<N; i++)
    ans[i] = -1;
  int used[N];
  memset(used, 0, sizeof(used));
  for(int i=0; i<N; i++){
    for(int j=0; j<N; j++){
      if (used[j])
        continue;
      if (A[i] == B[j]){
        ans [i] = j;
        used[j] = 1;
        break;
      }
    }
  }
 *rsz = N;
  return ans;
}
