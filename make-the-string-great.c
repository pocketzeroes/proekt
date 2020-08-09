char*makeGood(char*s){
    bool done = false;
    int asz;
    while(!done){
        done = true;
        int n = strlen(s);
        char*ans = calloc(100, sizeof(char));
        asz=0;
        for(int i=0; i<n; i++){
            if(i == n - 1 || abs(s[i] - s[i+1]) != 32){
                ans[asz++] = s[i];
            }
            else{
                done = false;
                i++;
            }
        }
        s = strdup(ans);
        free(ans);
    }
    return s;
}
