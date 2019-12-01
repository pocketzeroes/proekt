char board[3][3];

char get_winner(){
    for(int i=0; i<3; i++){
        if(board[0][i] != '.' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return board[0][i];
        if(board[i][0] != '.' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return board[i][0];
    }
    if(board[0][0] != '.' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return board[0][0];
    if(board[0][2] != '.' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return board[0][2];
    return '$';
}
char*tictactoe(int**moves, int movesSz, int*moves0sz){
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++)
            board[i][j] = '.';
    char turn = 'A';
    for(int z=0;z<movesSz;z++){int*move=moves[z];
        board[move[0]][move[1]] = turn;
        char winner = get_winner();
        if(winner != '$'){
            char*rv = strdup(" ");
            rv[0] = winner;
            return rv;
        }
        turn = 'A' + 'B' - turn;
    }
    return movesSz >= 9 ? "Draw" : "Pending";
}
