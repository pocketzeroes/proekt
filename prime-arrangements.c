enum{ MOD =(int) 1e9 + 7};

bool prime(int n) {
    if (n < 2)
        return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
            return false;
    return true;
}
int numPrimeArrangements(int n) {
    int prime_count = 0;
    for (int i = 2; i <= n; i++)
        if (prime(i))
            prime_count++;
    int remaining = n - prime_count;
    long long answer = 1;
    for (int i = 1; i <= remaining; i++)
        answer = answer * i % MOD;
    for (int i = 1; i <= prime_count; i++)
        answer = answer * i % MOD;
    return answer;
}
