int gcd(int a, int b) {
    while (b) {
        int c = a;
        a = b;
        b = c % b;
    }
    return a;
}
bool reachingPoints(int sx, int sy, int tx, int ty) {
    while (tx && ty) {
        if (tx < sx || ty < sy) 
            return false;
        if (ty > tx) {
            if (sx == tx && ty >= sy && (ty - sy) % tx == 0) 
                return true;
            ty %= tx;
        } 
        else if (tx > ty) {
            if (sy == ty && tx >= sx && (tx - sx) % ty == 0) 
                return true;
            tx %= ty;
        } 
        else {
            return false;
        }
    }
    return sx == tx && sy == ty;
}
