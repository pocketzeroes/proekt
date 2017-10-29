bool isOneBitCharacter(int*bits, int bitsSz){
    for(int i = 0;i < bitsSz; i++){
        if(i == bitsSz - 1 && bits[i] == 0)
            return true;
        if(bits[i] == 1)
            i++;
    }
    return false;
}
