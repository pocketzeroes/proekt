int getMaxRepetitions(char* s1, int n1, char* s2, int n2) {
    int rapport[102];memset(rapport,-1,sizeof(rapport));
    int rest   [102];memset(rest   ,-1,sizeof(rest   ));
    int b=-1;int posRest=0;int rap=0;
    int last=-1;
    rapport[0]=rest[0]=0;
    for(int i=1;i<=strlen(s2)+1;i++){
        int j;
        for(j=0;s1[j];j++){
            if(s2[posRest]==s1[j]){
                posRest++;
                if(posRest==strlen(s2)){
                    rap++;
                    posRest=0;
                }
            }
        }
        for(int k=0;k<i;k++){
            if(posRest==rest[k]){b=k;last=i;break;}
        }
        rapport[i]=rap;rest[i]=posRest;
        if(b>=0)break;
    }
    int interval=last-b;
    if(b>=n1)return rapport[n1]/n2;
    return ((n1-b)/interval*(rapport[last]-rapport[b])+rapport[(n1-b)%interval+b])/n2;
}
