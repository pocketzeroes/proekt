bool validPalindrome(char*s){
  int i, j, x, y, xx, yy;
  x=0; y = strlen(s)-1;
  while(y>x){
    if (s[x]==s[y])
      x++, y--;
    else 
      break;
  }
  if(x>=y) 
    return true;
  xx = x+1; yy = y;
  while(yy > xx){
    if (s[xx]==s[yy])
      xx++, yy--;
    else
      break;
  }
  if(xx>=yy) 
    return true;
  xx = x; yy = y-1;
  while(yy>xx){
    if(s[xx]==s[yy])
      xx++, yy--;
    else 
      break;
  }
  if(xx>=yy)
    return true;
  return false;
}
