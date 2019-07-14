int longestWPI(int*hours, int hoursSz){
    int n = hoursSz;
    for (int i = 0; i < n; i++)
        hours[i] = hours[i] > 8 ? +1 : -1;
    int sums[n+1]; memset(sums, 0, sizeof(sums));
    for (int i = 0; i < n; i++)
        sums[i + 1] = sums[i] + hours[i];
    int best = 0;
    for (int i = 0; i < n; i++)
        for (int j = n; j > i && j - i > best; j--)
            if (sums[i] < sums[j])
                best = j - i;
    return best;
}
