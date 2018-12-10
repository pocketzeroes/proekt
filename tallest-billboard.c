inline int max(int a,int b){return a>b?a:b;}

int d[25][5005];

int tallestBillboard(int*rods, int rodsSz){
    int n=rodsSz, i, j;
    memset(d, -1, sizeof(d));
    d[0][0] = 0;
    for(i=0;i<n;i++)
        for(j=0;j<=5000;j++)
            if(~d[i][j]){
                d[i+1][j] = max(d[i+1][j],d[i][j]);
                d[i+1][j+rods[i]] = max(d[i+1][j+rods[i]],d[i][j]+rods[i]);
                if(j>=rods[i])
                    d[i+1][j-rods[i]] = max(d[i+1][j-rods[i]],d[i][j]);
                else
                    d[i+1][rods[i]-j] = max(d[i+1][rods[i]-j],d[i][j]+rods[i]-j);
            }
    return d[n][0];
}
