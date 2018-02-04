bool canTransform(char*start, char*end){
    int start_size=strlen(start);
    int end_size  =strlen(end);
    if (start_size != end_size)
        return false;
    int n = start_size;
    int R = 0;
    for (int i = 0; i < n; i++) {
        if (start[i] == 'R') {
            R++;
        }
        else if (start[i] == 'L') {
            if (R != 0)
                return false;
        }
        if (end[i] == 'R') {
            R--;
            if (R < 0)
                return false;
        }
    }
    int L = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (start[i] == 'L') {
            L++;
        }
        else if (start[i] == 'R') {
            if (L != 0)
                return false;
        }
        if (end[i] == 'L') {
            L--;
            if (L < 0)
                return false;
        }
    }
    if (L != 0 || R != 0)
        return false;
    return true;
}
