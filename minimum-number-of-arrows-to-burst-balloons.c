inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int cmp(const void* a, const void* b) {
    int* pa = *(int**)a;
    int* pb = *(int**)b;
    int diff=pa[0]-pb[0];
    if(diff==0)return pa[1]-pb[1];
    return diff;
}
int findMinArrowShots(int** points, int pointsSz, int unused) {
    if (pointsSz==0)
        return 0;
    qsort(points, pointsSz,2*sizeof(int),cmp);
    int result = 0;
    for (int i = 0; i < pointsSz; ++i) {
        int j = i + 1;
        int right_bound = points[i][1];
        while (j < pointsSz && points[j][0] <= right_bound) {
            right_bound = min(right_bound, points[j][1]);
            ++j;
        }
        ++result;
        i = j - 1;
    }
    return result;
}
