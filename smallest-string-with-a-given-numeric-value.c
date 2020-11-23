char*string(int sz, char ch){
  char space[sz+1]; memset(space, ch , sizeof(space)); space[sz]='\0';
  return strdup(space);
}
char*getSmallestString(int n, int k){
    k -= n;
    char*s=string(n, 'a');
    for(int i=n-1; i>=0; --i){
        int d = fmin(k, 25);
        s[i] += d;
        k -= d;
    }
    return s;
}
