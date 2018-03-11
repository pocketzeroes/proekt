int score[100000];
int tmp[100000];

int bestRotation(int*a, int aSz){
  int i,j,n,bi,now,best;
  memset(score,0,sizeof(score));
  memset(tmp,0,sizeof(tmp));
  n = aSz;
  for (i=0;i<n;i++){
    if (a[i]<=i){
      tmp[0]++;
      tmp[i-a[i]+1]--;
      tmp[i+1]++;
      tmp[n]--;
    }
    else{
      tmp[i+1]++;
      tmp[n-(a[i]-i)+1]--;
    }
  }
  now=0;
  best=-1;
  bi=0;
  for (i=0;i<n;i++){
    now+=tmp[i];
    score[i]=now;
    if (now>best){
      best=now;
      bi=i;
    }
  }
  return bi;
}
