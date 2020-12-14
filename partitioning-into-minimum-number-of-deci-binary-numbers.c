int minPartitions(char*n){
    int mx = 0;
    for(int z=0;n[z];z++){char c = n[z];
        mx = fmax(mx, c - '0');
    }
    return mx;
}
