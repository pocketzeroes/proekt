int trap(int* height, int heightSize){
    int n     = heightSize;
    int level = 0;
    int water = 0;
    while(n--){
        int lower = *height < height[n] ? *height++ : height[n];
        if (lower > level) 
            level = lower;
        water += level - lower;
    }
    return water;
}
