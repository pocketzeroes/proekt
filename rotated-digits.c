int rotatedDigits(int n){
  int i,j,l,b1,b2,ans;
  char tmp[100];
  ans=0;
  for (i=1;i<=n;i++){
    sprintf(tmp,"%d",i);
    l=strlen(tmp);
    b1=0;b2=0;
    for (j=0;j<l;j++){
      if ((tmp[j]=='3')||(tmp[j]=='4')||(tmp[j]=='7'))
        b1=1;
      if ((tmp[j]=='2')||(tmp[j]=='5')||(tmp[j]=='6')||(tmp[j]=='9'))
        b2=1;
    }
    if ((b1==0)&&(b2==1)) 
      ans++;
  }
  return ans;
}
