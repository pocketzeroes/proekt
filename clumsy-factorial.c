typedef long long ll;
int clumsy(int N){
    if(N <= 2)
        return N;
    ll sum = N * (N - 1) / (N - 2);
    for(int n = N - 3; n > 0; n -= 4){
        sum += n;
        int next = 0;
        if (n - 1 > 0) next  = n - 1;
        if (n - 2 > 0) next *= n - 2;
        if (n - 3 > 0) next /= n - 3;
        sum -= next;
    }
    return sum;
}
