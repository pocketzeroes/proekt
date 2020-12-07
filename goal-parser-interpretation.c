char ans[100000];
int asz;
char*interpret(char*command){
    asz=0;
    int n=strlen(command),i;
    for(i=0;i<n;i++)
      if(command[i]=='G')
        ans[asz++] = 'G';
    else if(command[i+1]==')'){
        i++;
        ans[asz++] = 'o';
    }
    else{
        ans[asz++]='a';
        ans[asz++]='l';
        i+=3;
    }
    ans[asz]='\0';
    return strdup(ans);
}
