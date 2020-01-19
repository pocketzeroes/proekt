typedef long long ll;
int maximum69Number(int num){
    int ans = num;
    int pow = 1;
    while(pow <= num){
        long d = (num/pow)%10;
        if(d == 6)
            ans = fmax(ans, num+3*pow);
        pow *= 10;
    }
    return ans;
}
