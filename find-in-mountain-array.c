int findInMountainArray(int target, MountainArray*mountainArr){
    int n = length(mountainArr);
    int low = 1, high = n - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        int a = get(mountainArr, mid - 1),
            b = get(mountainArr, mid),
            c = get(mountainArr, mid + 1);
        if (a < b && b > c){
            low = high = mid;
            break;
        }
        if (a < b && b < c)
            low = mid + 1;
        else if (a > b && b > c)
            high = mid - 1;
        else
            assert(!"false");
    }
    int mountain = low;
    low = 0;
    high = mountain;
    while (low < high) {
        int mid = (low + high) / 2;
        if (get(mountainArr, mid) >= target)
            high = mid;
        else
            low = mid + 1;
    }
    if (get(mountainArr, low) == target)
        return low;
    low = mountain;
    high = n - 1;
    while (low < high) {
        int mid = (low + high) / 2;
        if (get(mountainArr, mid) <= target)
            high = mid;
        else
            low = mid + 1;
    }
    if (get(mountainArr, low) == target)
        return low;
    return -1;
}
