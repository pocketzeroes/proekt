bool judgeCircle(char* moves){
    int x = 0, y = 0;
    for (int i = 0; moves[i]; i++) {
        if (moves[i] == 'U') { y++; }
        if (moves[i] == 'D') { y--; }
        if (moves[i] == 'R') { x++; }
        if (moves[i] == 'L') { x--; }
    }
    return (x == 0 && y == 0);
}
