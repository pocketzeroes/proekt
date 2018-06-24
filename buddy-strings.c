bool buddyStrings(char*A, char*B){
    int Alength = strlen(A);
    int l[256]; memset(l, 0, sizeof(l));
    bool two = false;
    for(int i=0; i<Alength; i++)
        if(++l[A[i]] > 1)
            two = true;
    for(int i=0; B[i]; i++)
        --l[B[i]];
    for(int z=0;z<256;z++){int out = l[z];
        if(out != 0)
            return false;
    }
    int error = 0;
    for(int i = 0; i < Alength; i++)
        if(A[i] != B[i])
            error++;
    if(error == 2)
        return true;
    if(error > 2)
        return false;
    return two;
}
