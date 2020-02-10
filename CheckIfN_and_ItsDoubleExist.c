bool checkIfExist(int*arr, int arrSz){
    int N = arrSz;
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            if(i != j && arr[i] == arr[j] * 2)
                return true;
    return false;
}
