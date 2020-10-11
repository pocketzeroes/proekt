
int chmax(int*a, int b){
  if(*a<b){
    *a=b;
  }
  return *a;
}

int maxDepth(char*s){
  int i;
  int res = 0;
  int k = 0;
  for(i=(0);s[i];i++){
    if(s[i]=='('){
      k++;
    }
    if(s[i]==')'){
      k--;
    }
    chmax(&res, k);
  }
  return res;
}
