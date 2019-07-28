char res[100000];
int  rsz=0;
char*alphabetBoardPath(char*target){
    memset(res, 0, sizeof(res));
    rsz=0;
    int x = 0, y = 0;
    for (int i = 0; target[i]; ++i){
        int c = target[i] - 'a';
        int tx = c / 5,
            ty = c % 5;
        if (x != tx || y != ty) {
            if (x == 5) {
                while (tx != x) {
                    int dir = x < tx ? 1 : -1;
                    x += dir;
                    res[rsz++] = (dir < 0 ? 'U' : 'D');
                }
                while (ty != y) {
                    int dir = y < ty ? 1 : -1;
                    y += dir;
                    res[rsz++] = (dir < 0 ? 'L' : 'R');
                }
            } 
            else if (tx == 5) {
                while (ty != y) {
                    int dir = y < ty ? 1 : -1;
                    y += dir;
                    res[rsz++] = (dir < 0 ? 'L' : 'R');
                }
                while (tx != x) {
                    int dir = x < tx ? 1 : -1;
                    x += dir;
                    res[rsz++] = (dir < 0 ? 'U' : 'D');
                }
            } 
            else {
                while (tx != x) {
                    int dir = x < tx ? 1 : -1;
                    x += dir;
                    res[rsz++] = (dir < 0 ? 'U' : 'D');
                }
                while (ty != y) {
                    int dir = y < ty ? 1 : -1;
                    y += dir;
                    res[rsz++] = (dir < 0 ? 'L' : 'R');
                }
            }
        }
        res[rsz++] = '!';
    }
    return strdup(res);
}
