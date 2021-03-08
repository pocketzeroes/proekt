int nearestValidPoint(int x, int y, int**points, int pointsSz, int*points0sz){
    int ans = -1, dis = INT_MAX, i = 0;
    for(int z=0;z<pointsSz;z++){int*p = points[z];
        if(p[0] == x || p[1] == y){
            int d = abs(p[0] - x) + abs(p[1] - y);
            if(d < dis){
                dis = d;
                ans = i;
            }
        }
        i += 1;
    }
    return ans;
}
