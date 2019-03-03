int min(int a,int b){return a<b?a:b;}

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

int cnt[26];
int num[26];

char**commonChars(char**A, int Asz, int*rsz){
    int i;
    for(i=0; i<26; ++i)
        cnt[i]=100000;
    for(int z=0;z<Asz;z++){char*s=A[z];
        for(i=0;i<26;++i)
            num[i]=0;
        for(int i=0; s[i]; ++i){
            num[s[i]-'a']++;
        }
        for(i=0;i<26;++i) 
            cnt[i]=min(cnt[i],num[i]);
    }
    vecs vec=newVecS();
    for(i=0; i<26; ++i){
        if(cnt[i]>0){
            char*s=strdup(" ");
            char ch='a'+i;
            s[0] = ch;
            for(int j=0; j<cnt[i]; ++j){
                vec.ptr = pushbackS(vec.ptr, &vec.sz, s);
            }
        }
    }
   *rsz=vec.sz;
    return vec.ptr;
}
