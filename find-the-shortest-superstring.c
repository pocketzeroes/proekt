int max(int a,int b){return a>b?a:b;}
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
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
//////////////////////////////////////

char*shortestSuperstring(char**A, int Asz){
    int n=Asz, m=0, i, j, k, o, a[12][12], l[12], p[12], f[4096][12];
    for(i=0; i<n; i++)
        l[i] = strlen(A[i]);
    memset(f, 0, sizeof(f));
    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            if(i!=j)
                for(a[i][j]=0,k=1; k<l[i]&&k<l[j]; k++){
                    for(o=0; o<k; o++)
                        if(A[i][l[i]-k+o] != A[j][o])
                            break;
                    if(o==k)
                        a[i][j]=k;
                }
    for(i=1; i<1<<n; i++)
        for(j=0; j<n; j++)
            if(i>>j&1)
                for(k=0; k<n; k++)
                    if((i>>k&1) && j!=k)
                        f[i][j] = max(f[i][j], f[i^(1<<j)][k]+a[k][j]);
    for(i=j=0; i<n; i++)
        if(f[(1<<n)-1][i]>f[(1<<n)-1][j])
            j=i;
    for(i=(1<<n)-1;;){
        p[m++]=j;
        if(i==(1<<j))
            break;
        for(k=0; k<n; k++)
            if((i>>k&1)&&j!=k&&f[i][j] == f[i^(1<<j)][k]+a[k][j])
                break;
        i^=1<<j;
        j=k;
    }
    reverse(p, 0, m-1);
    char*ans = strdup(A[p[0]]);
    for(i=1; i<n; i++)
        for(j=a[p[i-1]][p[i]]; j<l[p[i]]; j++)
            ans = concatc(ans, A[p[i]][j]);
    return ans;
}
