#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}

int*findAnagrams(char*s,char*p,int*rsz) {
    int*result=NULL;
    int slen=strlen(s);
    int plen=strlen(p);
    if (slen==0 ||plen==0)
        return result;
    int cnts[26];memset(cnts,0,sizeof(cnts));
    for (int i=0;i<plen;i++){
        char c=p[i];
        ++cnts[c - 'a'];
    }
    for (int left = 0, right = 0; s[right]; ++right) {
        --cnts[s[right] - 'a'];
        while (left <= right && cnts[s[right] - 'a'] < 0) 
            ++cnts[s[left++] - 'a'];
        if (right - left + 1 == plen)
            result=pushback(result,rsz,left);
    }
    return result;
}
