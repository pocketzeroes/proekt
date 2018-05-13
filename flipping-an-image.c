void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
int**flipAndInvertImage(int**A, int Asz, int*A0sz, int**colsz, int*rsz){
    int**B = calloc(Asz, sizeof(int*));
    for(int i=0; i<Asz; i++)
        B[i] = calloc(A0sz[i], sizeof(int));
    int*cols = calloc(Asz, sizeof(int));
    
    for(int i=0;i<Asz;i++){int*e = A[i];
        reverse(e, 0, A0sz[i]-1);
        for(int j=0;j<A0sz[i];j++){
            e[j] = 1-e[j];
        }
    }
    
    for(int i=0; i<Asz; i++)
        cols[i] = A0sz[i];
    for(int i=0; i<Asz; i++)
      for(int j=0;j<A0sz[i];j++)
          B[i][j] = A[i][j];
    
   *colsz = cols;
   *rsz = Asz;
    return B;
}
