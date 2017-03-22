bool checkscramble(char* s1, char* s2, int size) {
    bool o1, o2;
    int i, val1=0, val2=0, val3 =0, val4 =0;
    if (size == 2 && ((s1[0] == s2[0] && s1[1] == s2[1]) || (s1[0] == s2[1] && s1[1] == s2[0])))
        return true;
    else if (size == 2)
        return false;
    if (size ==1 && s1[0] == s2[0])
        return true;
    else if (size == 1)
        return false;
    for (i =0;i<size;i++) {
        val1 += s1[i];
        val2 += s2[i];
        val3 += s1[i] * (s1[i] & 2);
        val4 += s2[i] * (s2[i] & 2);
    }
    if (val1 != val2 || val3 != val4)
        return false;
    for (i=1; i < size; i++) {
        o1=checkscramble( s1, s2, i);
        o2=checkscramble( s1+i, s2+i, size-i);
        if (o1 && o2)
            return true;
        o1=checkscramble( (s1+(size-i)), s2, i);
        o2=checkscramble( s1, s2+i, size-i);
        if (o1 && o2)
            return true;
    }
    return false;
}

bool isScramble(char* s1, char* s2) {
    int size = strlen(s1);
    return checkscramble(s1, s2, size);
}

