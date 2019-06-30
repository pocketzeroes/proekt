int min(int a,int b){return a<b?a:b;}

int*distributeCandies(int candies, int n, int*rsz){
    int*answer = calloc(n, sizeof(int));
    int count = 1;
    while (candies > 0) {
        for (int i = 0; i < n; i++) {
            int take = min(count, candies);
            answer[i] += take;
            candies -= take;
            count++;
        }
    }
   *rsz = n;
    return answer;
}
