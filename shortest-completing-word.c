
bool isLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
char toLower(char c) {
  if (c >= 'A' && c <= 'Z') return c - 'A' + 'a';
  else return c;
}
char* shortestCompletingWord(char*p, char**w, int wSz){
  int cntp[26] = {};
  for(int i=(0); p[i]; i++) {
    if (isLetter(p[i]))
      cntp[toLower(p[i]) - 'a']++;
  }
  char*ans = strdup("");
  for(int i=(0);i<(wSz);i++) {
    char*s = w[i];
    int cnt[26] = {};
    for(int j=(0); s[j]; j++)
      cnt[toLower(s[j]) - 'a']++;
    bool ok = true;
    for(int c=(0);c<(26);c++)
      if (cnt[c] < cntp[c])
        ok = false;
    if (ok) {
      if(strlen(ans) == 0 || strlen(w[i]) < strlen(ans))
        ans = w[i];
    }
  }
  return ans;
}
