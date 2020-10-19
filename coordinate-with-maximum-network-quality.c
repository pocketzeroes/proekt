double dis(int x1, int y1, int x2, int y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
int*bestCoordinate(int**towers, int towersSz, int*towers0sz, int radius, int*rsz){
    int ans_x, ans_y, ans_d = 0;
    for(int i = -100; i <= 100; i++){
        for(int j = -100; j <= 100; j++){
            int tot_d = 0;
            for(int z=0;z<towersSz;z++){int*t = towers[z];
                double d = dis(i, j, t[0], t[1]);
                if (d <= radius)
                    tot_d += (int)(floor(t[2] / (1 + d)));
            }
            if(ans_d < tot_d){
                ans_d = tot_d;
                ans_x = i;
                ans_y = j;
            }
        }
    }
    int*rv=calloc(2, sizeof(int));
    rv[0]=ans_x;
    rv[1]=ans_y;
   *rsz=2;
    return rv;
}
