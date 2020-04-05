char ans[100000];
int  asz;
char*longestDiverseString(int a, int b, int c){
    asz=0;
    int p[3];
    p[0] = a; p[1] = b; p[2] = c;
    int last = -1;
    while(1){
        int mx = 0, which = -1;
        for(int i = 0; i < 3; ++i){
            if(i != last && p[i] > mx){
                mx = p[i];
                which = i;
            }
        }
        if(which == -1)
            break;
        int mxprev = fmax(p[0], fmax(p[1], p[2]));
        p[which] -= 2;
        int mxsuff = fmax(p[0], fmax(p[1], p[2]));
        p[which] += 2;
        if(mxprev - 2 == mxsuff){
            ans[asz++]=(char)(which + 97);
            ans[asz++]=(char)(which + 97);
            p[which] -= 2;
        }
        else{
            ans[asz++]=(char)(which + 97);
            --p[which];
        }
        last = which;
    }
    ans[asz]='\0';
    return strdup(ans);
}
