int findTheDistanceValue(int*arr1, int arr1Sz, int*arr2, int arr2Sz, int d){
    int ret = 0;
    for(int z=0;z<arr1Sz;z++){int v = arr1[z];
        bool f = true;
        for(int q=0;q<arr2Sz;q++){int x = arr2[q];
            if(abs(v - x) <= d)
                f = false;
        }
        ret += f;
    }
    return ret;
}
