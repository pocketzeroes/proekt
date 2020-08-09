
int minInsertions(char*s){
  int ssize=strlen(s);
  int i;
  int res = 0;
  int k = 0;
  for(i=(0);s[i];i++){
    if(s[i]=='('){
      k++;
    }
    else{
      k--;
      if(i+1 < ssize && s[i+1]==')'){
        i++;
      }
      else{
        res++;
      }
    }
    if(k < 0){
      k++;
      res++;
    }
  }
  return res + 2 * k;
}
