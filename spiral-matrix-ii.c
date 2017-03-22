int** generateMatrix(int n) {
    if (n == 0) 
        return NULL;
    int** spiral = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i) 
        spiral[i] = (int*)malloc(sizeof(int) * n);
    int low = 0, high = n - 1, k = 1;
    for (; low < high; ++low, --high) {
        for (int i = low; i < high; ++i, ++k) spiral[low] [i] = k;
        for (int i = low; i < high; ++i, ++k) spiral[i][high] = k;
        for (int i = high; i > low; --i, ++k) spiral[high][i] = k;
        for (int i = high; i > low; --i, ++k) spiral[i] [low] = k;
    }
    if (low == high) 
        spiral[low][low] = k;
    return spiral;
}

