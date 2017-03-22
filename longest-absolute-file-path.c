inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int lengthLongestPath(char*input){
    int maxi=0,count=0,ln=1;
    bool isFile=false;
    int level[200];
    memset(level,0,sizeof(level));
    for(int i=0,fin=strlen(input);i<fin;++i){
        while(input[i]=='\t'){
            ++ln;++i;
        }
        while(input[i]!='\n'&&i<fin){
            if(input[i]=='.')isFile=true;
            ++count;++i;
        }
        if(isFile){
            maxi=max(maxi,level[ln-1]+count);
        }
        else{
            level[ln]=level[ln-1]+count+1;
        }
        count=0;ln=1;isFile=false;
    }
    return maxi;
}
