int min(int a,int b){return a<b?a:b;}
int max_element(int*arr, int sz){
  int maxe=arr[0];
  for(int i=1;i<sz;i++)
    if(arr[i]>maxe)
      maxe=arr[i];
  return maxe;
}
int*maxDepthAfterSplit(char*seq, int*rsz){
    int n = strlen(seq);
    int levels[n+1]; memset(levels, 0, sizeof(levels));
    for(int i = 0; i < n; i++)
        levels[i + 1] = levels[i] + (seq[i] == '(' ? +1 : -1);
    int max_level = max_element(levels, n+1);
    int half = max_level / 2;
    int*answer=calloc(n, sizeof(int));
    for(int i = 0; i < n; i++)
        answer[i] = min(levels[i], levels[i + 1]) < half ? 1 : 0;
   *rsz = n;
    return answer;
}
