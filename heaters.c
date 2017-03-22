inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int cmp (const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

int Bsearch(int*nums,int sz, int val) {
    int l = 0, r = sz - 1;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (nums[mid] == val)
            return mid;
        else if (nums[mid] < val)
            l = mid + 1;
        else
            r = mid - 1;
    }
    return l;
}
int findRadius(int* houses, int housesSize, int* heaters, int heatersSize) {
    int house_size = housesSize;
    if (house_size == 0) return 0;
    qsort(heaters, heatersSize, sizeof(int),cmp);
    int res = 0;
    for(int i=0;i<housesSize;i++){
        int c = houses[i];
        int idx = Bsearch(heaters,heatersSize, c);
        if (idx == 0) {
            res = max(res, heaters[idx] - c);
        } else if (idx >= heatersSize) {
            res = max(res, c - heaters[heatersSize-1]);
        } else {
            res = max(res, min(heaters[idx] - c, c - heaters[idx - 1]));
        }
    }
    return res;
}
