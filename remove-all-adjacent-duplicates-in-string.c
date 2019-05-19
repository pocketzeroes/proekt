char buff[500000];
int  buffSz;
char*removeDuplicates(char*S){
  buffSz=0;
  for(int i=0;S[i];i++){char c=S[i];
    if(buffSz==0 || buff[buffSz-1]!=c)
      buff[buffSz++]=c;
    else
      buffSz--;
  }
  buff[buffSz]='\0';
  return strdup(buff);
}
