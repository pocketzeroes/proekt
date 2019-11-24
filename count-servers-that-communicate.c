#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)

int countServers(int**g, int gSz, int*g0sz){
    int H = gSz,
        W = g0sz[0];
    int ch[H];clr(ch);
    int cw[W];clr(cw);
    for(int i=(0),i_end_=(H);i<i_end_;i++)
        for(int j=(0),j_end_=(W);j<j_end_;j++)
            if(g[i][j])
                ch[i]++,
                cw[j]++;
    int retbad = 0,
        ret = 0;
    for(int i=(0),i_end_=(H);i<i_end_;i++)
        for(int j=(0),j_end_=(W);j<j_end_;j++){
            ret    += g[i][j];
            retbad +=(g[i][j] && ch[i] == 1 && cw[j] == 1);
        }
    return ret - retbad;
}
