bool checkPerfectNumber(int num) {
    int set[5] = {6, 28, 496, 8128, 33550336};
    for( int i=0;i<5;i++)
        if(num == set[i])
            return true;
    return false;
}
