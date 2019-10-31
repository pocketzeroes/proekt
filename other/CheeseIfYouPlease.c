#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>


enum{ MAXCHEESES = 50                    };
enum{ MAXBLENDS  = 50                    };
enum{ MAXROWS    = MAXCHEESES+1          };
enum{ MAXCOLS    = MAXCHEESES+MAXBLENDS+1};
const double TOL = 0.000000001;


int getPivotCol(int ncols, double row0[]){
    for(int i=0; i<ncols-1; i++)
        if (row0[i] > 0.0)
        return i;
    return -1;
}

double simplex(int nrows, int ncols, double array[][MAXCOLS]){
    int pcol, prow;
    while((pcol = getPivotCol(ncols, array[0])) != -1){
        prow = -1;
        double minval;
        for(int i=1; i<nrows; i++) {
            if (array[i][pcol] <= 0.0)
                continue;
            if (prow == -1 || array[i][ncols-1]/array[i][pcol] < minval) {
                prow = i;
                minval = array[i][ncols-1]/array[i][pcol];
            }
        }
        assert(prow != -1);
        for(int i=0; i<nrows; i++) {
            if (i == prow) {
                double factor = array[prow][pcol];
                for(int j=0; j<ncols; j++)
                    array[i][j] /= factor;
            }
            else {
                double factor = array[i][pcol]/array[prow][pcol];
                for(int j=0; j<ncols; j++) {
                    array[i][j] -= array[prow][j]*factor;
                    if (fabs(array[i][j]) < TOL)
                        array[i][j] = 0.0;
                }
            }
        }
    }
    return array[0][ncols-1];
}
int main(){
    double array[MAXROWS][MAXCOLS];
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i=0; i<n+1; i++)
        for(int j=0; j<n+m+1; j++)
            array[i][j] = 0.0;
    for(int i=1; i<=n; i++)
        scanf("%lf", &array[i][n+m]);
    for(int j=0; j<m; j++) {
        for(int i=1; i<=n; i++){
            scanf("%lf", &array[i][j]);
			array[i][j] /= 100.0;
        }
        scanf("%lf", &array[0][j]);
    }
    for(int j=m; j<n+m; j++)
        array[j-m+1][j] = 1.0;
    double max = simplex(n+1, n+m+1, array);
    printf("%.2lf\n", -max);
    return 0;
}
