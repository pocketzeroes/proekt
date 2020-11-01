
int countSubstrings(char*s, char*t){
  int ssize=strlen(s);
  int tsize=strlen(t);
  int i;
  int j;
  int k;
  int f;
  int res = 0;
  for(i=(0);i<ssize;i++){
    for(j=(0);j<tsize;j++){
      k = f = 0;
      for(;;){
        if(i+k >= ssize || j+k >= tsize){
          break;
        }
        if(s[i+k] != t[j+k]){
          f++;
        }
        if(f >= 2){
          break;
        }
        if(f==1){
          res++;
        }
        k++;
      }
    }
  }
  return res;
}
