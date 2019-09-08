int countLetters(char*S){
  int i, j, res=0;
  for(i=0; S[i]; i++){
    if(i && S[i]==S[i-1]){
      j++;
    }
    else{
      j = 1;
    }
    res += j;
  }
  return res;
}