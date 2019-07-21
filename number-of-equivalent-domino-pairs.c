typedef long long ll;
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

int numEquivDominoPairs(int**domino, int dominoSz, int*domino0sz){
    int num[10][10]={};
    ll  ret=0;
    for(int z=0;z<dominoSz;z++){int*d=domino[z];
        int a=min(d[0],d[1]);
        int b=max(d[0],d[1]);
        ret+=num[a][b];
        num[a][b]++;
    }
    return ret;
}
