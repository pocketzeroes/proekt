int balancedString(char*s){
    char CHARS[4] = "QWER";
    int n = strlen(s);
    int*counts[4];
    for(int c = 0; c < 4; c++) {
        counts[c]=calloc(n+1, sizeof(int));
        for (int i = 0; i < n; i++)
            counts[c][i + 1] = counts[c][i] + (s[i] == CHARS[c] ? 1 : 0);
    }
    int low = 0, high = n;
    while (low < high) {
        int mid = (low + high) / 2;
        bool works = false;
        for (int i = 0; i + mid <= n; i++) {
            int now[4];
            bool good = true;
            for (int c = 0; c < 4; c++) {
                now[c] = counts[c][i] + (counts[c][n] - counts[c][i + mid]);
                if (now[c] > n / 4)
                    good = false;
            }
            works = works || good;
        }
        if (works)
            high = mid;
        else
            low = mid + 1;
    }
    return low;
}
