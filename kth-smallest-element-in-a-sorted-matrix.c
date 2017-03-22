int kthSmallest(int** matrix, int n, int useless, int k) {
    int small=matrix[0][0], big=matrix[n-1][n-1], mid, cnt, i, j;
    while(small<big) {
        mid=small+big>>1;
        cnt=0;
        j=n-1;
        for(i=0;i<n;i++) {
            while(j>=0&&matrix[i][j]>mid) --j;
            cnt+=j+1;
        }
        if(cnt<k) small=mid+1;
        else big=mid;
    }
    return big;
}
