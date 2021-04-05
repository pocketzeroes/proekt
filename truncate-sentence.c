char*truncateSentence(char*s, int k){
  int cnt = 0;
  for(int i=0; s[i]; ++i){
    if(s[i] == ' '){
      cnt++;
      if(cnt == k){
        s[i]='\0';
        return strdup(s);
      }
    }
  }
  return strdup(s);
}
