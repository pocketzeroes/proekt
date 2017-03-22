bool isSelfCrossing(int* x, int xSize) {
    if (xSize >= 5 && x[3] == x[1] && x[4] + x[0] >= x[2]) 
        return true;
    for (int i = 3; i < xSize; ++i){
        if (x[i] >= x[i - 2] && x[i - 3] >= x[i - 1]) 
            return true;
        else if (i >= 5 && x[i - 4] <= x[i - 2] && x[i] + x[i - 4] >= x[i - 2] && x[i - 1] <= x[i - 3] && x[i - 1] + x[i - 5] >= x[i - 3])
            return true;
    }
    return false;
}
