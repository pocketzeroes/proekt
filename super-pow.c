int myPow(int a, int n, int b) {
    int result = 1;
    int x = a % b;
    while (n) {
        if (n & 1) {
            result = result * x % b;
        }
        n >>= 1;
        x = x * x % b;
    }
    return result % b;
}
int superPow(int a, int* b, int bSize) {
    int result = 1;
    for (int i=0;i<bSize;i++){
        int digit=b[i];
        result = myPow(result, 10, 1337) * myPow(a, digit, 1337) % 1337;
    }
    return result;
}
