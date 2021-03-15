bool areAlmostEqual(char*s1, char*s2){
  int n = strlen(s1);
  int f[26]={0};
  for(int i=0; i<n; i++){
    f[s1[i]-'a']++;
    f[s2[i]-'a']--;
  }
  for(int i=0; i<26; i++){
    if(f[i] != 0)
      return false;
  }
  int diff = 0;
  for(int i=0; i<n; i++){
    if(s1[i] != s2[i]){
      diff++;
    }
  }
  return diff <= 2;
}
