bool validUtf8(int* data, int dataSize) {
    int count = 0;
    int c;
    for ( int i=0; i < dataSize ; i++ ) {
        c=data[i];
        if (count == 0) {
            if ((c >> 5) == 0x6)
                count = 1;
            else if ((c >> 4) == 0xe)
                count = 2;
            else if ((c >> 3) == 0x1e)
                count = 3;
            else if ((c >> 7))
                return false;
        }
        else {
            if ((c >> 6) != 0x2)
                return false;
            --count;
        }
    }
    return count == 0;
}
