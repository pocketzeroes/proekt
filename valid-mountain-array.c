bool validMountainArray(int*A, int Asz){
    int n = Asz, i, j;
    if(n<3)
        return 0;
    for(i=1;i<n;i++)
        if(A[i]<=A[i-1])
            break;
    if(i==n)
        return 0;
    i--;
    for(j=n-2;~j;j--)
        if(A[j]<=A[j+1])
            break;
    if(!~j)
        return 0;
    j++;
    return i==j;
}
