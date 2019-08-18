int*conv(char*s){
  int*res = calloc(26, sizeof(int));
  for(int i=0;s[i];i++){char c=s[i];
    res[c-'a']++;
  }
  return res;
}
int check(int*as, int*bs){
  for(int i=0; i<26; i++)
    if(as[i]>bs[i]) 
      return 0;
  return 1;
}
int countCharacters(char**words, int wordsSz, char*chars){
  int ans = 0;
  int*base = conv(chars);
  for(int i=0;i<wordsSz;i++){char*w=words[i];
    if(check(conv(w),base))
      ans += strlen(w);
  }
  return ans;
}
