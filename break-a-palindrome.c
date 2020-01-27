char*breakPalindrome(char*palindrome){
  int palindrome_size = strlen(palindrome);
  if(palindrome_size<2)
    return"";
  int ST = 97, ED = 98;
  for(int i=ST;i<=ED;i++){
    for(int pos=0;pos<palindrome_size/2; pos++){
      int posNumb = (int) palindrome[pos];
      if( i != posNumb){
        int target_pos = i < posNumb ? pos : palindrome_size-1-pos;
        palindrome[target_pos] = (char) i;
        return palindrome;
      }
    }
  }
  return NULL;
}
