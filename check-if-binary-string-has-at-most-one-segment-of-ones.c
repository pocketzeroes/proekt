bool checkOnesSegment(char*s){
  int i;
  for(i=(1); s[i]; i++){
    if(s[i-1]=='0' && s[i]=='1'){
      return false;
    }
  }
  return true;
}
