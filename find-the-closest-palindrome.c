
char* nearestPalindromic(char* num) {
    int i;
    int n= strlen(num);
    long long int llorigin;
    sscanf(num, "%lld", &llorigin);
    if(n==1){
        if(num[0]=='0') num[0]='1';
        else num[0]-=1;
        return num;
    }
    for(i=0;i<n;i++){
        if(num[i]!='9') break;
    }
    if(i==n){
        char*ptr=NULL;
        asprintf(&ptr, "%lld", llorigin+2);
        return ptr;
    }
    for(i=0;i+i<n;i++){
        if(num[i]!=num[n-i-1]) break;
    }
    if(i+i>=n){ 
        if(n%2==1){
            if(num[n/2]=='0') num[n/2]='1';
            else num[n/2]=num[n/2]-1;
        }
        else{
            if(num[n/2]=='0'){
                num[n/2]='1';
                num[n/2-1]='1';
            }
            else{
                num[n/2]-=1;
                num[n/2-1]-=1;
            }
        }
        long long int ll999=1;
        for(int i=0;i<n;i++){
            ll999*=10;
        }
        ll999=ll999/10-1;
        long long int llnum;
        sscanf(num, "%lld", &llnum);
        if(llabs(llorigin-llnum) >= llabs(llorigin-ll999)){
            char*ptr=NULL;
            asprintf(&ptr, "%lld", ll999);
            return ptr;
        }
        return num;
    }
    long long int ll999=1;
    for(int i=n-1;i>=0;i--){
        num[i]=num[n-i-1];
        ll999*=10;
    }
    ll999=ll999/10-1;
    long long int llnum;
    sscanf(num, "%lld", &llnum);
    long long int llnumUp=0, llnumDown=0;
    if(num[n/2]!='9'){
        num[n-1-n/2]=num[n/2]=num[n/2]+1;
        sscanf(num, "%lld", &llnumUp);
        num[n-1-n/2]=num[n/2]=num[n/2]-1;
    }
    if(num[n/2]!='0'){
        num[n-1-n/2]=num[n/2]=num[n/2]-1;
        sscanf(num, "%lld", &llnumDown);
        num[n-1-n/2]=num[n/2]=num[n/2]+1;
    }
    int cnddNum=4;
    long long int candidate[cnddNum];
    candidate[0]=llnum;
    candidate[1]=ll999;
    candidate[2]=llnumUp;
    candidate[3]=llnumDown;
    long long int min=9223372036854775807L, res=0;
    for(int i=0;i<cnddNum;i++){
        long long int d=llabs(llorigin-candidate[i]);
        if(min>d || (min==d && candidate[i]<res)){
            min=d;
            res=candidate[i];
        }
    }
    char*ptr=NULL;
    asprintf(&ptr, "%lld", res);
    return ptr;
}



















































