#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

int*diStringMatch(char*S, int*rsz){
    int n=strlen(S), i, j;
    vec ans = newVec();
    ans.ptr = pushback(ans.ptr, &ans.sz, 0);
    for(i=0; i<n; i++)
        if(S[i] == 'I')
            ans.ptr = pushback(ans.ptr, &ans.sz, i+1);
    else{
        ans.ptr = pushback(ans.ptr, &ans.sz, 0);
        for(j=0; j<=i; j++)
            ans.ptr[j]++;
    }
   *rsz=   ans.sz;
    return ans.ptr;
}
