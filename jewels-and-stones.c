int numJewelsInStones(char*Je, char*S){
  int Jelen= strlen(Je);
  int Slen = strlen(S );
  int i, j, ans;
  ans = 0;
  for(i=0; i<Slen; i++){
    for(j=0; j<Jelen; j++)
      if (S[i]==Je[j])
        break;
    if(j<Jelen)
      ans++;
  }
  return ans;
}
