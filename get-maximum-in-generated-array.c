int arr[101];

int getMaximumGenerated(int n){
  int i;
  arr[0] = 0;
  arr[1] = 1;
  for(i=(2);i<(n+1);i++){
    if(i%2==0){
      arr[i] = arr[i/2];
    }
    if(i%2==1){
      arr[i] = arr[i/2] + arr[i/2+1];
    }
  }
  {
    int Q5VJL1cS;
    int e98WHCEY;
    if(n+1==0){
      e98WHCEY = 0;
    }
    else{
      e98WHCEY = arr[0];
      for(Q5VJL1cS=(1);Q5VJL1cS<(n+1);Q5VJL1cS++){
        e98WHCEY = fmax(e98WHCEY, arr[Q5VJL1cS]);
      }
    }
    return e98WHCEY;
  }
}
