int countPrimes(int n) {
    if (n <= 2) 
        return 0;
    int num = n / 2;
    int*is_prime=malloc(n*sizeof(int));
    memset(is_prime,1,n*sizeof(int));
    for (int i = 3; i * i < n; i += 2) {
        if (!is_prime[i])
            continue;
        for (int j = i * i; j < n; j += 2 * i) {
            if (!is_prime[j]) 
                continue;
            --num;
            is_prime[j] = false;
        }
    }
    return num;
}
