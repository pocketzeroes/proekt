
bool good(char**b){
    for (int i = 0; i < (3); ++i){
        if(b[i][0]!=' '&&b[i][1]==b[i][0]&&b[i][2]==b[i][0])
            return 0;
        if(b[0][i]!=' '&&b[1][i]==b[0][i]&&b[2][i]==b[0][i])
            return 0;
    }
    if(b[0][0]!=' '&&b[1][1]==b[0][0]&&b[2][2]==b[0][0])
        return 0;
    if(b[0][2]!=' '&&b[1][1]==b[0][2]&&b[2][0]==b[0][2])
        return 0;
    return 1;
}
bool validTicTacToe(char**b, int bSz){
    int d[2] = {0,0};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j){
        if(b[i][j]=='X')
            d[0]++;
        else if(b[i][j]=='O')
            d[1]++;
    }
    if(d[0]==d[1]+1){
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j){
                if(b[i][j]=='X'){
                    b[i][j]=' ';
                    if(good(b))
                        return 1;
                    b[i][j]='X';
                }
            }
        return 0;
    }
    else if(d[0]==d[1]){
        if(d[0]==0)
            return 1;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j){
                if(b[i][j]=='O'){
                    b[i][j]=' ';
                    if(good(b))
                        return 1;
                    b[i][j]='O';
                }
            }
        return 0;
    }
    else 
        return 0;
}
