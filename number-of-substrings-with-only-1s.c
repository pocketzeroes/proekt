enum{ MOD = 1000000007};

int numSub(char*s){
    int ret = 0;
    int one = 0;
    for(int i=0; s[i]; i++){
      if(s[i] == '0')
          one = 0;
      else
          one++;
      ret += one;
      ret %= MOD;
    }
    return ret;
}
