inline int max(int a,int b){return a>b?a:b;}

int findLUSlength(char* a, char* b){
    if(strcmp(a,b)==0)
        return -1;
    return max(strlen(a), strlen(b));
}
