char*src;
int dp[2005][2005];
int id[2005][2005];
int casenum;

int dfs(int lhs, int rhs){
  if(lhs > rhs)
    return 0;
  if(lhs == rhs)
    return 1;
  if(id[lhs][rhs] == casenum)
    return dp[lhs][rhs];
  id[lhs][rhs] = casenum;
  dp[lhs][rhs] = casenum;
  if(src[lhs] == src[rhs])
    dp[lhs][rhs] = 2 + dfs(lhs+1, rhs-1);
  else
    dp[lhs][rhs] = fmax(dfs(lhs+1, rhs), dfs(lhs, rhs-1));
  return dp[lhs][rhs];
}
int longestPalindrome(char*word1, char*word2){
  int w1sz=strlen(word1);
  int w2sz=strlen(word2);
  casenum++;
  src = calloc(w1sz+w2sz+1, sizeof(char));
  strcat(src, word1);
  strcat(src, word2);
  int ret = 0;
  for(int i = 0; i < w1sz; i++)
    for(int j = 0; j < w2sz; j++)
      if(word1[i] == word2[j])
        ret = fmax(ret, 2 + dfs(i+1, w1sz + j - 1));
  free(src);
  return ret;
}
