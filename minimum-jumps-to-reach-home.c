enum{oo=1000000000};
bool c[4005];
int d[4005][2],qx[9005],qy[9005],he,ta;

int minimumJumps(int*forbidden, int forbiddenSz, int a, int b, int x){
    memset(d,-1,sizeof(d));
    memset(c,0,sizeof(c));
    for(int z=0;z<forbiddenSz;z++){int f=forbidden[z];
      c[f]=1;
    }
    he=ta=0;
    d[qx[ta]=0][qy[ta]=1]=0;
    ta++;
    int i,j;
    while(he!=ta){
        i=qx[he];
        j=qy[he++];
        if(i+a<4005&&!c[i+a]&&!~d[i+a][1]){
            d[qx[ta]=i+a][qy[ta]=1]=d[i][j]+1;
            ta++;
        }
        if(i>=b&&j&&!c[i-b]&&!~d[i-b][0]){
            d[qx[ta]=i-b][qy[ta]=0]=d[i][j]+1;
            ta++;
        }
    }
    if(!~d[x][0])return d[x][1];
    if(!~d[x][1])return d[x][0];
    return fmin(d[x][0],d[x][1]);
}
