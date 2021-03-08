bool checkPowersOfThree(int n) {
    for(; n; n /= 3) if(n % 3 == 2) return false;
    return true;
}
