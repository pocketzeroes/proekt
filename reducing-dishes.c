int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int maxSatisfaction(int*satisfaction, int satisfactionSz){
    qsort(satisfaction, satisfactionSz, sizeof(int), cmp);
    int ans = 0;
    for(int x = 0; x < satisfactionSz; x++){
        int sum = 0;
        for(int i = x; i < satisfactionSz; i++)
            sum += satisfaction[i] * (i + 1 - x);
        ans = fmax(ans, sum);
    }
    return ans;
}
