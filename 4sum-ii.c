void quickSort(int* arr, int begin, int end){
    int l = begin, r = end;
    int v = arr[l+((r-l)>>1)];
    while(l <= r){
        while(arr[l] < v) l++;
        while(arr[r] > v) r--;
        if(l <= r){
            int t = arr[l];
            arr[l] = arr[r];
            arr[r] = t;
            l++;
            r--;
        }
    }
    if(begin < r) quickSort(arr, begin, r);
    if(l < end) quickSort(arr, l, end);
}

int lowerBound(int*arr, int size, int target){
    int l = 0, r = size-1;
    while(l <= r){
        int m = l+((r-l)>>1);
        if(arr[m] >= target) r = m-1;
        else l = m+1;
    }
    return arr[l]==target? l : -1;
}

int upperBound(int*arr, int size, int target){
    int l = 0, r = size-1;
    while(l <= r){
        int m = l+((r-l)>>1);
        if(arr[m] <= target) l = m+1;
        else r = m-1;
    }
    return arr[r]==target? r : -1;
}
int fourSumCount(int* A, int ASize, int* B, int BSize, int* C, int CSize, int* D, int DSize) {
    int size1 = ASize*BSize, size2 = CSize*DSize;
    int *arr1 = (int*)malloc(sizeof(int)*size1), *arr2 = (int*)malloc(sizeof(int)*size2);
    int k = 0;
    for(int i = 0; i < ASize; ++i)
        for(int j = 0; j < BSize; ++j)
            arr1[k++] = A[i]+B[j];
    k = 0;
    for(int i = 0; i < CSize; ++i)
        for(int j = 0; j < DSize; ++j)
            arr2[k++] = C[i]+D[j];
    quickSort(arr1, 0, size1-1);
    quickSort(arr2, 0, size2-1);
    int sumCount = 0;
    for(int i = 0; i < size1; ++i){
        int l = lowerBound(arr2, size2, -arr1[i]);
        if(l != -1){
            int r = upperBound(arr2, size2, -arr1[i]);
            sumCount += r-l+1;
        }
    }
    return sumCount;
}



