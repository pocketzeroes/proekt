#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct vecS {
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int*partitionLabels(char*S, int*rsz){
    int cntall[26]; memset(cntall, 0, sizeof(cntall));
    for(int i=0;S[i];i++){char c = S[i];
        ++cntall[c-'a'];
    }
    vec ans = newVec();
    int cntnow[26]; memset(cntnow, 0, sizeof(cntnow));
    int start = 0;
    for(int end=0; S[end]; ++end){
        ++cntnow[S[end]-'a'];
        bool valid = true;
        for (int i=0; i<26; ++i)
            if (cntnow[i]!=0 && cntnow[i]!=cntall[i]) {
                valid = false;
                break;
            }
        if (valid) {
            ans.ptr = pushback(ans.ptr, &ans.sz, end-start+1);
            memset(cntnow, 0, sizeof(cntnow));
            start = end+1;
        }
    }
   *rsz=   ans.sz;
    return ans.ptr;
}
