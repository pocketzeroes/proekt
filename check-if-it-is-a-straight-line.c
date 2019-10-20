typedef long long ll;
bool checkStraightLine(int**c, int cSz, int*c0sz){
    for (int i=2; i<cSz; i++){
        ll dx  = c[0][0] - c[1][0];
        ll dy  = c[0][1] - c[1][1];
        ll ddx = c[0][0] - c[i][0];
        ll ddy = c[0][1] - c[i][1];
        if(dx * ddy != dy * ddx)
            return false;
    }
    return true;
}
