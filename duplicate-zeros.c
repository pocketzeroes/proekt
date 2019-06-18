void duplicateZeros(int*arr, int n){
  int*a = calloc(n, sizeof(int));
  for(int i=0; i<n; i++)
    a[i] = arr[i];
  int p = 0;
  for(int i=0; i<n; i++){
    if(a[i]==0){
      if(p < n)
        arr[p++] = 0;
      if(p < n)
        arr[p++] = 0;
    }
    else if(p < n)
      arr[p++] = a[i];
  }
}
