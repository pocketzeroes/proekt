int max(int a,int b){return a>b?a:b;}

int longestMountain(int*A, int Asz){
    int ret = 0;
    for(int i=1; i<Asz-1; i++){
        if(A[i] <= A[i-1] || A[i] <= A[i+1]) 
            continue;
        int low = i;
        int curr = 1;
        while(low > 0 && A[low] > A[low-1]){
            low--;
            curr++;
        }
        int high = i;
        while(high + 1 < Asz && A[high] > A[high+1]){
            curr++;
            high++;
        }
        ret = max(ret, curr);
    }
    return ret;
}
