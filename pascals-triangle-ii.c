int*getRow(int rowIndex , int*rsz){
    int sz=rowIndex + 1;
    int*result=malloc(sz*sizeof(int));
    memset(result,0,sz*sizeof(int));
    for (int i = 0; i < sz; ++i){
        int prev_result = result[0] = 1;
        for (int j = 1; j <= i; ++j) {
            int tmp = result[j];
            result[j] += prev_result;
            prev_result = tmp;
        }
    }
   *rsz=sz;
    return result;
}
