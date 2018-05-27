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
/////////////
int check(char*S1, char*S2){
    int cnt = 0;
    for(int i=0; i<6; ++i){
        if(S1[i] == S2[i]) 
            ++cnt;
    }
    return cnt;
}
void findSecretWord(char**wordlist, int wordlistSz, Master*master){
    for(int i=0; i<10; ++i){
        int idx = rand() % wordlistSz;
        char*target = wordlist[idx];
        int r = guess(master, target);
        if (r == 6)
            return;
        vecs newlist = newVecS();
        for(int z=0;z<wordlistSz;z++){char*s = wordlist[z];
            if(check(s, target) == r){
                newlist.ptr = pushbackS(newlist.ptr, &newlist.sz, s);
            }
        }
        wordlist   = newlist.ptr;
        wordlistSz = newlist.sz;
    }
}
