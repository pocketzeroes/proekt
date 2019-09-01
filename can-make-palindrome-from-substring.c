bool*canMakePaliQueries(char*s, int**queries, int queriesSz, int*queries0sz, int*rsz){
    int n = strlen(s);
    int freq[26][n+1]; memset(freq, 0, sizeof(freq));
    for (int c = 0; c < 26; c++)
        for (int i = 0; i < n; i++)
            freq[c][i + 1] = freq[c][i] + (s[i] == 'a' + c ? 1 : 0);
    bool*answer = calloc(queriesSz, sizeof(bool));
    for(int z=0;z<queriesSz;z++){int*query = queries[z];
        int left = query[0], 
           right = query[1], 
               k = query[2];
        right++;
        int odd_count = 0;
        for (int c = 0; c < 26; c++)
            if ((freq[c][right] - freq[c][left]) % 2 != 0)
                odd_count++;
        answer[z] = odd_count <= 2 * k + 1;
    }
   *rsz=   queriesSz;
    return answer;
}
