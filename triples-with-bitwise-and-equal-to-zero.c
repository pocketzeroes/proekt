int countTriplets(int*A, int Asz){
    int f[1<<16]; memset(f, 0, sizeof(f));
    for(int i=0;i<Asz;i++){int v = A[i];
        f[v]++;
    }
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 1<<16; j++){
            if(j<<~i>=0){
                f[j] += f[j|1<<i];
            }
        }
    }
    for(int i = 0; i < 1<<16; i++){
        f[i] = f[i] * f[i] * f[i];
    }
    for(int i = 0; i < 16; i++){
        for(int j = 0; j < 1<<16; j++){
            if(j<<~i>=0){
                f[j] -= f[j|1<<i];
            }
        }
    }
    return f[0];
}
