
bool isv(char ch){
  char voels[] = "aeiouAEIOU";
  for(int z=0;voels[z];z++)
    if(ch==voels[z])
      return true;
  return false;
}
bool halvesAreAlike(char*s){
    int n = strlen(s);
    int lhs = 0;
    int rhs = 0;
    for(int i=0; i<n; i++){
      if(isv(s[i])){
        if(i < n/2)
          lhs++;
        else
          rhs++;
      }
    }
    return lhs == rhs;      
}
