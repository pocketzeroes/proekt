char buff[100000];
char*to(char*s){
    char*a = buff;
    int aSz=0;
    for(int z=0; s[z]; z++){ char c = s[z];
        if(c=='#'){
            if(aSz>0) 
               aSz--;
        }
        else{
            a[aSz++]=c;
        }
    }
    a[aSz]='\0';
    return strdup(a);
}
bool backspaceCompare(char*S, char*T){
    return(strcmp(to(S), to(T))==0);
}
