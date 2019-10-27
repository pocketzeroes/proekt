#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
int result;

void maxLength4(int i, int length, bool*count, char**arr, int arrsz){
    if(i == arrsz)
        result = fmax(result, length);
    else{
        maxLength4(i+1, length, count, arr, arrsz);
        bool clone[26]; memcpy(clone, count, 26*sizeof(bool));
        for(int z=0;arr[i][z];z++){char c = arr[i][z];
            if(!clone[c-'a'])
                clone[c-'a'] = true;
            else
                return;
        }
        maxLength4(i+1, length+strlen(arr[i]), clone, arr, arrsz);
    }
}
int maxLength(char**arr, int arrSz){
    result = 0;
    bool newbool[26]; clr(newbool);
    maxLength4(0, 0, newbool, arr, arrSz);
    return result;
}
