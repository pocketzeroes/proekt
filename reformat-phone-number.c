char ret[100000];
int rsz;

char*reformatNumber(char*number){
  rsz=0;
  char*v=strdup(number);
  int vsz=0;
  for(int z=0;number[z];z++){char x=number[z];
    if(x>='0'&&x<='9')
      v[vsz++]=x;
  }
  while(vsz>4){
    if(rsz)
      ret[rsz++] = '-';
    for(int i=0; i<3; i++){
      ret[rsz++] = v[0];
      v++;
      vsz--;
    }
  }
  if(rsz)
    ret[rsz++]= '-';
  if(vsz == 2){
    ret[rsz++]= v[0];
    ret[rsz++]= v[1];
  }
  else if(vsz == 3){
    ret[rsz++]= v[0];
    ret[rsz++]= v[1];
    ret[rsz++]= v[2];
  }
  else{
    ret[rsz++] = v[0];
    ret[rsz++] = v[1];
    ret[rsz++] = '-';
    ret[rsz++] = v[2];
    ret[rsz++] = v[3];
  }
  ret[rsz]='\0';
  return strdup(ret);
}
