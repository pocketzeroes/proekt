int max(int a,int b){return a>b?a:b;}
int arrayNesting(int* nums, int numslength){
  int n = numslength;
  bool visited[n];memset(visited, 0, sizeof(visited));
  int answer = 0;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      int cur = i;
      int count = 0;
      do {
        visited[cur] = true;
        cur = nums[cur];
        count++;
      } while (cur != i);
      answer = max(answer, count);
    }
  }
  return answer;
}
