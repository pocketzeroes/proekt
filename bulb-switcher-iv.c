int minFlips(char*target){
  int pre=0;
  int ret=0;
  for(int z=0;target[z];z++){char c=target[z];
    if(c%2!=pre){
      ret++;
      pre^=1;
    }
  }
  return ret;
}
