char*  convert(char*  s, int numRows) {
    if (numRows == 1)
        return s;
    int step = 2 * numRows - 2;
    int size = strlen(s);
    char* zigzag=malloc(size*2);
    int zigzagLen=0;
    for (int i = 0; i < numRows; ++i) {
        for (int j = i; j < size; j += step) {
            zigzag[zigzagLen++]=s[j];
            if (0 < i && i < numRows - 1 && j + step - 2 * i < size) {
                zigzag[zigzagLen++]=s[j + step - 2 * i];
            }
        }
    }
    zigzag[zigzagLen]='\0';
    return zigzag;
}

