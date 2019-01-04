#pragma GCC optimize "-O3"
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
    char**output = resizeArray(array, char*, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
    char**ptr;
    int sz;
}vecs;
vecs newVecS(){
    vecs rez;
    rez.ptr = NULL;
    rez.sz  = 0;
    return rez;
}

char**spellchecker(char**wordlist, int wordlistSz, char**queries, int queriesSz, int*rsz){
    int n = wordlistSz,
        m = queriesSz;
    vecs ans = newVecS();
    for(int i=0; i<m; i++){
        int len = strlen(queries[i]);
        int f=0;
        for(int j=0; j<n; j++){
            if(strcmp(wordlist[j], queries[i])==0){
                ans.ptr = pushbackS(ans.ptr, &ans.sz, wordlist[j]);
                f=1;
                break;
            }
        }
        if(f)
            continue;
        for(int j=0; j<n; j++){
            int lens = strlen(wordlist[j]);
            if(len!=lens)
                continue;
            int ok=1;
            for(int k=0; k<len; k++){
                char a = queries [i][k],
                     b = wordlist[j][k];
                if(a>='A'&&a<='Z')
                    a=a-'A'+'a';
                if(b>='A'&&b<='Z')
                    b=b-'A'+'a';
                if(!(a==b)){
                    ok=0;
                    break;
                }
            }
            if(ok){
                ans.ptr = pushbackS(ans.ptr, &ans.sz, wordlist[j]);
                f=1;
                break;
            }
        }
        if(f)
            continue;
        for(int j=0; j<n; j++){
            int lens = strlen(wordlist[j]);
            if(len!=lens)
                continue;
            int ok=1;
            for(int k=0; k<len; k++){
                char a=queries [i][k],
                     b=wordlist[j][k];
                if(a>='A'&&a<='Z')
                    a=a-'A'+'a';
                if(b>='A'&&b<='Z')
                    b=b-'A'+'a';
                if(!((a==b)||((a=='a'||a=='e'||a=='i'||a=='o'||a=='u')&&(b=='a'||b=='e'||b=='i'||b=='o'||b=='u')))){
                    ok=0;
                    break;
                }
            }
            if(ok){
                ans.ptr = pushbackS(ans.ptr, &ans.sz, wordlist[j]);
                f=1;
                break;
            }
        }
        if(!f){
            ans.ptr = pushbackS(ans.ptr, &ans.sz, strdup(""));
        }
    }
   *rsz=   ans.sz;
    return ans.ptr;
}
