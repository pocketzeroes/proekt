int gcd(int a, int b){
    while (b > 0) {
        int c = a;
        a = b;
        b = c % b;
    }
    return a;
}
bool hasGroupsSizeX(int*deck, int deckSz){
    int f[10001] = {0};
    for(int z=0;z<deckSz;z++){int d = deck[z];
        f[d]++;
    }
    int g = 0;
    for(int z=0; z<10001; z++){int v = f[z];
        g = gcd(g, v);
    }
    return g != 1;
}
