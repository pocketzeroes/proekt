int in1[100];
int ou1[100];

int maximumRequests(int n, int**requests, int requestsSz, int*requests0sz){
    int i,j,k,m,b1,cnt,ans;
    m=requestsSz;
    ans=0;
    for (i=0;i<(1<<m);i++){
        memset(in1,0,sizeof(in1));
        memset(ou1,0,sizeof(ou1));
        cnt=0;
        for (j=0;j<m;j++){
            if (((1<<j)&i)!=0){
                cnt++;
                ou1[requests[j][0]]++;
                in1[requests[j][1]]++;
            }
        }
        b1=1;
        for (j=0;j<n;j++)
            if (in1[j]!=ou1[j])
                b1=0;
        if (b1==1){
            if (cnt>ans)
                ans=cnt;
        }
    }
    return ans;
}
