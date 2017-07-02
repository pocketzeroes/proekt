bool judgeSquareSum(int c) {
    for(long long a=0;a*a<=c;a++) {
        long long l=0,r=(c-a*a),m=0;
        while(l<=r) {
            m=(l+r)/2;
            if(a*a+m*m==c) return true;
            if(a*a+m*m>c) { r = m-1; }
            else {l = m+1; }
        }
    }
    return false;
}
