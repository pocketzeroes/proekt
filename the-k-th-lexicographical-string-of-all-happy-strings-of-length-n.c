int po[20];

char u[100000];
int usz;

char*getHappyString(int n, int k){
    po[0]=1;
    for(int i=1;i<=n;++i)
        po[i]=po[i-1]*2;
    if(k>po[n-1]*3)
        return "";
    int l=0;
    usz=0;
    for(int i=1;i<=n;++i){
        for(int j='a';j<='c';++j){
            if(l!=j){
                if(k>po[n-i])
                    k-=po[n-i];
                else{
                    u[usz++] = j;
                    l=j;
                    break;
                }
            }
        }
    }
    u[usz]='\0';
    return strdup(u);
}
