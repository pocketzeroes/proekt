int gcd(int a, int b) {
    while (b != 0) {
        int tmp = b;
        b = a % b;
        a = tmp;
    }
    return a;
}
bool canMeasureWater(int x, int y, int z) {
    return z == 0 || (z <= x + y && z % gcd(x, y) == 0);
}
