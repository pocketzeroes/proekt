int Alength;
int Blength;
bool same(char*A, char*B, int rotation){
    for(int i = 0; i < Alength; i++)
        if(B[i] != A[(i + rotation) % Alength])
            return false;
    return true;
}
bool rotateString(char*A, char*B){
    Alength = strlen(A);
    Blength = strlen(B);
    if(Alength != Blength)
        return false;
    for(int rotation = 0; rotation < Alength; rotation++)
        if(same(A, B, rotation))
            return true;
    return false;
}
