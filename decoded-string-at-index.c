typedef long long ll;
char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}
char*decodeAtIndex(char*S, int K){
  ll len = 0;
  char*curs = "";
  for(int i=0; S[i]; i++){
    if('0' <= S[i] && S[i] <= '9'){
      int t = S[i] - '0';
      if (len * t >= K)
        return decodeAtIndex(substr(S, 0, i), (K - 1) % len + 1);
      len *= t;
      curs = "";
    }
    else{
      len++;
      curs += S[i];
      if(len == K){
        char*ans = strdup(" ");
        ans[0] = S[i];
        return ans;
      }
    }
  }
  return "";
}
