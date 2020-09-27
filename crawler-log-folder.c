int minOperations(char**logs, int logsSz){
    int ans=0;
    int i, j;
    for(i=0; i<logsSz; i++){
        if(strcmp(logs[i], "../")==0){
            if(ans>0) 
               ans--;
        }
        else if(strcmp(logs[i], "./")==0)
            ;
        else 
            ans++;
    }
    return ans;
}
