char*getn(char*s){
  s[4]++;
  if(s[4]=='0'+10){
    s[3]++;
    s[4]='0';
  }
  if(s[3]=='6'){
    s[1]++;
    s[3]='0';
    s[4]='0';
  }
  if(s[1]=='0'+10){
    s[0]++;
    s[1]='0';
  }
  if((s[0]=='2')&&(s[1]=='4')){
    s[0]='0';
    s[1]='0';
  }
  return s;
}
char*nextClosestTime(char*time){
  int i, j, b1, b2;
  char*s = strdup(time);
  while(1){
    s = getn(s);
    b2=1;
    for(i=0; s[i]; i++){
      b1=0;
      if (i==2)
        continue;
      for (j=0; time[j]; j++)
        if(s[i]==time[j])
          b1=1;
      if (b1==0)
        b2=0;
    }
    if (b2==1)
      return s;
  }
  return time;
}



