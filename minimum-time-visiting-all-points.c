int minTimeToVisitAllPoints(int**p, int pSz, int*p0sz){
    int x = p[0][0],
        y = p[0][1];
    int ret = 0;
    for(int z=0;z<pSz;z++){int*v = p[z];
        int nx = v[0],
            ny = v[1];
        ret += fmax(abs(nx - x),
                    abs(ny - y));
        x = nx,
        y = ny;
    }
    return ret;
}
