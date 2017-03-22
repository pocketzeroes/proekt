#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int maxArea(int* height,int heightSize){
    int maxarea = 0, l = 0, r = heightSize - 1;
    while (l < r) {
        maxarea = MAX(maxarea, MIN(height[l], height[r]) * (r - l));
        if (height[l] < height[r])
            l++;
        else
            r--;
    }
    return maxarea;
}
