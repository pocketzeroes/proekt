void amax(int*x, int y){
    if(*x<y)
      *x=y;
}
int maximumScore(int a, int b, int c){
    int ans = 0;
    if(a + b <= c) amax(&ans, a+b);
    else if(a + c <= b) amax(&ans, a + c);
    else if(b + c <= a) amax(&ans, b + c);
    else amax(&ans, (a+b+c) / 2);
    return ans;
}
