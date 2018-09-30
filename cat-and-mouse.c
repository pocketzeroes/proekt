int catMouseGame(int**g, int gSz, int*g0sz){
    int n = gSz;
    int win[2][n*n];
    memset(win, 0, sizeof(win));
    for(int i=0; i<n; i++){
        win[0][i] = 1;
        win[1][i] = 1;
    }
    for(int i=1; i<n; i++){
        win[0][i*n+i] = 2;
        win[1][i*n+i] = 2;
    }
    while(1){
        bool anew = false;
        for(int m=0; m<n; m++){
            for(int c=1; c<n; c++){
                if(win[0][m*n+c] == 0){
                    bool und = false;
                    for(int z=0;z<g0sz[m];z++){int e = g[m][z];
                        if(win[1][e*n+c] == 1){
                            win[0][m*n+c] = 1;
                            anew = true;
                            goto inner;
                        }
                        if(win[1][e*n+c] == 0){
                            und = true;
                        }
                    }
                    if(!und){
                        win[0][m*n+c] = 2;
                        anew = true;
                    }
                }
            }
       inner:;
        }
        for(int c=1; c<n; c++){
            for(int m=0; m<n; m++){
                if(win[1][m*n+c] == 0){
                    bool und = false;
                    for(int z=0; z<g0sz[c]; z++){int e = g[c][z];
                        if(e == 0)
                            continue;
                        if(win[0][m*n+e] == 2){
                            win[1][m*n+c] = 2;
                            anew = true;
                            goto innerloop;
                        }
                        if(win[0][m*n+e] == 0){
                            und = true;
                        }
                    }
                    if(!und){
                        win[1][m*n+c] = 1;
                        anew = true;
                    }
                }
            }
      innerloop:;
        }
        if(!anew)
            break;
    }
    return win[0][1*n+2];
}
