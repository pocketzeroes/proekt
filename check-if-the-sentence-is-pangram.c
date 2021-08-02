bool checkIfPangram(char*s){
  int i;
  int cnt[26] = {0};
  for(i=(0);s[i];i++){
    cnt[s[i]-'a'] = 1;
  }
  int Q5VJL1cS;
  int e98WHCEY;
  if(26==0){
    e98WHCEY = 0;
  }
  else{
    e98WHCEY = cnt[0];
    for(Q5VJL1cS=(1);Q5VJL1cS<(26);Q5VJL1cS++){
      e98WHCEY += cnt[Q5VJL1cS];
    }
  }
  return e98WHCEY== 26;
}
