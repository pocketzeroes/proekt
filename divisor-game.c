bool divisorGame(int N){
    bool v[N+1]; memset(v, 0, sizeof(v));
    for(int i=0; i<N; i++){
        if(!v[i]){
            for(int j=1; i+j<=N &&j<i+j; j++)
                if((i+j)%j == 0)
                    v[i+j] = true;
        }
    }
    return v[N];
}
