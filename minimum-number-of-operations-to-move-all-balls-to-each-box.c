bool present[2005];
int*minOperations(char*boxes, int*rsz){
  int n = strlen(boxes);
  for(int i=0; i<n; i++)
    present[i] = boxes[i] == '1';
  int*ret=calloc(n,sizeof(int));
  int dec = 0;
  for(int i=0; i<n; i++){
    if(present[i]){
      dec++;
      ret[0] += i;
    }
  }
  if(present[0])
    dec -= 2;
  for(int i=1; i<n; i++){
    ret[i] = ret[i-1] - dec;
    if(present[i])
      dec -= 2;
  }
 *rsz=n;
  return ret;
}
