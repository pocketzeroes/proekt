bool threeConsecutiveOdds(int*arr, int arrSz){
    for(int i = 0; i + 2 < arrSz; i++){
      if(arr[i]%2 && arr[i+1]%2 && arr[i+2]%2)
          return true;
    }
    return false;
}
