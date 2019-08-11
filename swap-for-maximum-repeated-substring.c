int S[202020][26];

int maxRepOpt1(char*text){
  memset(S,0,sizeof(S));
  int N=strlen(text);
  int i,j;
  for(i=0;i<(N);i++){
   text[i]-='a';
   for(j=0;j<(26);j++)
     S[i+1][j]=S[i][j];
   S[i+1][text[i]]++;
  }
  int ma=0;
  for(i=0;i<(N);i++) {
   int c=text[i];
   int cur=i+1;
   for(j=20;j>=0;j--)
     if(cur+(1<<j)<=N) {
       if(S[cur+(1<<j)][c]-S[i][c]>=cur+(1<<j)-i-1)
         cur+=1<<j;
     }
   if(S[cur][c]-S[i][c]==cur-i) {
    ma = fmax(ma,cur-i);
   }
   else{
    if(S[cur][c]-S[i][c]==S[N][c])
      ma=fmax(ma,cur-i-1);
    else
      ma=fmax(ma,cur-i);
   }
  }
  return ma;
}
