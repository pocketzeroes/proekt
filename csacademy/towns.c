#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int main(){
    int n, x;
    while(scanf("%d%d", &n, &x)==2){
        int l[n];
        int v[n];
        for(int i=0; i<n; i++) scanf("%d", &l[i]);
        for(int i=0; i<n; i++) scanf("%d", &v[i]);
        double lastAns;
        int f(double z){
            lastAns = 0;
            int cnt = 0;
            for(int i=0; i<n; i++){
                if(z * v[i] * (v[i] + 1) >= l[i]){
                    lastAns += l[i] * 1.0 / v[i];
                    continue;
                }
                double D  = z * z + 4 * l[i] * z;
                double vv = (-z + sqrt(D)) / (2 * z);
                assert(vv >= 0);
                int cv = ceil(vv);
                assert(cv >= v[i]);
                cnt += cv - v[i];
                lastAns += l[i] * 1.0 / cv;
            }
            return cnt;
        }
        double L = 0, R = 2e4;
        for (int it = 0; it < 100; it++){
            double M = (L + R) / 2.0;
            if (f(M) <= x) 
                R = M;
            else 
                L = M;
        }
        int k = f(R);
        lastAns -= (x - k) * R;
        printf("%.15f\n", lastAns);
    }
    return 0;
}
