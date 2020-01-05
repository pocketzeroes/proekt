char res[100000];
int  rsz;
char*freqAlphabets(char*s){
    rsz=0;
    int ssize = strlen(s);
    for(int i=0; s[i]!=0; i++){
        if(i+2<ssize){
            if(s[i+2]=='#'){
                res[rsz++] = (char)((s[i]-'0')*10+s[i+1]-'1'+'a');
                i += 2;
            }
            else
                res[rsz++] = (char)(s[i]-'1'+'a');
        }
        else
            res[rsz++] = (char)(s[i]-'1'+'a');
    }
    res[rsz]='\0';
    return strdup(res);
}
