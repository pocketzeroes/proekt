#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}

int countBalls(int lowLimit, int highLimit){
    int v[50]; clr(v);
    for(int i=lowLimit; i<=highLimit; i++){
        int s = 0;
        for(int j=i; j; j/=10)
          s += j % 10;
        v[s]++;
    }
    return max_element(v, 50);
}
