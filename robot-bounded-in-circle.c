int dx[] = {0, -1, 0, 1};
int dy[] = {1, 0, -1, 0};

bool isRobotBounded(char*ins){
    int x = 0, y = 0;
    int dir = 0;
    for(int i=0; ins[i]; i++){
        char c = ins[i];
        if (c == 'L')
            dir = dir + 1;
        else if (c == 'R')
            dir = dir + 3;
        else {
            x += dx[dir];
            y += dy[dir];
        }
        dir %= 4;
    }   
    if (dir != 0)
        return true;
    if (x == 0 && y == 0)
        return true;
    return false;
}
