int min(int a,int b){return a<b?a:b;}
void swap(char*nums, int i, int j) {
   char t  = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void dfs(int*ans, int N, char*A, char*B, int pos, int cur){
    if(N == pos){
       *ans = min(*ans, cur);
        return ;
    }
    if(cur > N || cur > *ans) 
        return;
    if(A[pos] == B[pos]) 
        dfs(ans, N, A, B, pos + 1, cur);
    else{
        for(int i = pos + 1; i < N; i++){
            if(B[i] == A[pos]){
                swap(B, pos, i);
                dfs(ans, N, A, B, pos + 1, cur + 1);
                swap(B, pos, i);
            }
        }
    }
}
int kSimilarity(char*A, char*B){
    int N = strlen(A), ans = INT_MAX;
    dfs(&ans, N, A, B, 0, 0);
    return ans;
}
