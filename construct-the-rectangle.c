int* constructRectangle(int area, int* returnSize) {
    if (area <= 0) return NULL;
    int w = area;
    for (int i = 1; i * i <= area; ++i) {
        if (area % i == 0) 
            w = i;
    }
    int rez=malloc(2*sizeof(int));
    rez[0]=area / w;
    rez[1]=w;
    *returnSize=2;
    return rez;
}
