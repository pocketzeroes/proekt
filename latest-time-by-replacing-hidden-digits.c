char*maximumTime(char*time){
  int i;
  char*res;
  char buf[7];
  for(i=(0);i<(24);i++){
    int j;
    for(j=(0);j<(60);j++){
      int k;
      sprintf(buf,"%02d:%02d",i,j);
      for(k=(0);k<(5);k++){
        if(time[k]!='?' && time[k]!=buf[k]){
          goto Q5VJL1cS;
        }
      }
      res = strdup(buf);
    Q5VJL1cS:;
    }
  }
  return res;
}
