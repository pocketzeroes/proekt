char* substr(const char* str, size_t begin, size_t len) 
{
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
} 

int nxt[20010][26];

char*minWindow(char*s, char*t){
  int n = strlen(s);
  int m = strlen(t);
  for(int i = 0; i < 26; ++i)
    nxt[n][i] = n;
  for(int i = n - 1; i >= 0; --i) {
    for(int j = 0; j < 26; ++j)
      nxt[i][j] = nxt[i + 1][j];
    nxt[i][s[i] - 'a'] = i;
  }
  int l = 0, r = n + 10;
  for(int i = 0; i < n; ++i) {
    int j = 0;
    int p = i;
    while(p < n && j < m) {
      p = nxt[p][t[j] - 'a'];
      if(p < n) {
        p++;
        j++;
      }
    }
    if(j == m && p - i < r - l) {
      r = p;
      l = i;
    }
  }
  if(r > n)
    return strdup("");
  return substr(s, l, r - l);
}
