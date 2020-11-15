#define swap(a,b) do{ __typeof(a) tp; tp=a; a=b; b=tp; }while(0)

int pw[6];
int dp[729][7][7], dq[729][7][7];

int getMaxGridHappiness(int m, int n, int introvertsCount, int extrovertsCount){
    if(m < n)
      swap(m, n);
    for(int i = 0; i <= n; i += 1)
      pw[i] = i ? pw[i - 1] * 3 : 1;
    for(int i = 0; i < pw[n]; i += 1)
        for(int j = 0; j <= introvertsCount; j += 1)
            for(int k = 0; k <= extrovertsCount; k += 1)
                dp[i][j][k] = -1000000;
    dp[0][0][0] = 0;
    for(int i = 0; i < m; i += 1)
        for(int j = 0; j < n; j += 1){
            for(int mask = 0; mask < pw[n]; mask += 1)
                for(int x = 0; x <= introvertsCount; x += 1)
                    for(int y = 0; y <= extrovertsCount; y += 1)
                        dq[mask][x][y] = -1000000;
            for(int mask = 0; mask < pw[n]; mask += 1)
                for(int x = 0; x <= introvertsCount; x += 1)
                    for(int y = 0; y <= extrovertsCount; y += 1) 
                      if(dp[mask][x][y] >= 0){
                        if(x < introvertsCount){
                            int d = 120;
                            if(mask / pw[n - 1] == 1) d -= 60;
                            if(mask / pw[n - 1] == 2) d -= 10;
                            if(j && mask % 3 == 1) d -= 60;
                            if(j && mask % 3 == 2) d -= 10;
                            int nmask = mask * 3 % pw[n] + 1;
                            dq[nmask][x + 1][y] = fmax(dq[nmask][x + 1][y], dp[mask][x][y] + d);
                        }
                        if(y < extrovertsCount){
                            int d = 40;
                            if(mask / pw[n - 1] == 1) d -= 10;
                            if(mask / pw[n - 1] == 2) d += 40;
                            if(j && mask % 3 == 1) d -= 10;
                            if(j && mask % 3 == 2) d += 40;
                            int nmask = mask * 3 % pw[n] + 2;
                            dq[nmask][x][y + 1] = fmax(dq[nmask][x][y + 1], dp[mask][x][y] + d);
                        }
                        int nmask = mask * 3 % pw[n];
                        dq[nmask][x][y] = fmax(dq[nmask][x][y], dp[mask][x][y]);
                      }
            for(int mask = 0; mask < pw[n]; mask += 1)
                for(int x = 0; x <= introvertsCount; x += 1)
                    for(int y = 0; y <= extrovertsCount; y += 1)
                        dp[mask][x][y] = dq[mask][x][y];
        }
    int ans = 0;
    for(int mask = 0; mask < pw[n]; mask += 1)
        for(int x = 0; x <= introvertsCount; x += 1)
            for(int y = 0; y <= extrovertsCount; y += 1)
                ans = fmax(ans, dp[mask][x][y]);
    return ans;
}
