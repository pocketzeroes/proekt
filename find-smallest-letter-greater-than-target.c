int upper_bound(char*a, int n, char x){
    int l = 0;
    int h = n;
    while (l < h) {
        int mid = (l + h) / 2;
        if (x >= a[mid])
            l = mid + 1;
        else
            h = mid;
    }
    return l;
}
char nextGreatestLetter(char*a, int aSz, char target){
    int it = upper_bound(a, aSz, target);
    if(it != aSz)
        return a[it];
    return a[0];
}
