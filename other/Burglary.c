#include<stdio.h>
#include<stdlib.h>

enum{ MAXN = 1000};
enum{ MAXM = 5000};
enum{ MAXL = 10  };
#define lad '|'
#define emptyslot '-'

int n,m;
int candy[MAXN][MAXM];
int sumcandyleft[MAXN][MAXM];
int closestcandyleft[MAXN][MAXM];
int closestcandyright[MAXN][MAXM];
int upladders[MAXN+1][MAXL];
int countupladders[MAXN+1];

void readData() {
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int i,j;
    scanf("%d %d", &n, &m);
    read = getline(&line, &len, stdin);
    for (i = 0; i<n;++i){
        read = getline(&line, &len, stdin);
        for (j = 0; j<m; ++j) {
            if (line[j] != emptyslot) 
                candy[i][j] = line[j]-48;
            else
                candy[i][j] = 0;
        }      
        read = getline(&line, &len, stdin);       
        for (j = 0; j<m; ++j) 
          if (line[j] == lad) {
            upladders[i+1][countupladders[i+1]] = j;
            countupladders[i+1]++;
          }
    }
}
int getmaxcandybetween(int shelf, int l1, int l2, int wleft, int wright){
    int totalcandy;
    totalcandy = sumcandyleft[shelf][l2]-sumcandyleft[shelf][l1]+candy[shelf][l1];
    if (wleft && closestcandyleft[shelf][l1]!=-1) 
        totalcandy += candy[shelf][closestcandyleft[shelf][l1]];
    if (wright && closestcandyright[shelf][l2]!=-1) 
        totalcandy += candy[shelf][closestcandyright[shelf][l2]];
    return totalcandy;       
}
int getmaxcandy(int shelf, int l1, int l2, int pl1, int pl2){
    int aux, totalcandy, intersect, endinner, flag;
    if (l1>pl1){
        aux = l1;
        l1 = pl1;
        pl1 = aux;
    }
    if (l2>pl2){
        aux = l2;
        l2 = pl2;
        pl2 = aux;
    }
    if (l1>l2){
        aux = l1;
        l1 = l2;
        l2 = aux;
        aux = pl1;
        pl1 = pl2;
        pl2 = aux;
    }
    totalcandy = 0;
    if (l2>pl1) {
        flag = closestcandyleft[shelf][l2]>pl1? 1:0;
        totalcandy += getmaxcandybetween(shelf, l2, pl2, flag, 1);
        flag = closestcandyright[shelf][pl1]<l2 && closestcandyright[shelf][pl1]!=closestcandyleft[shelf][l2]? 1:0;
        totalcandy += getmaxcandybetween(shelf, l1, pl1, 1, flag); 
    }
    else {
        endinner = pl1;
        if (pl2 < pl1)
            endinner = pl2;
        intersect = sumcandyleft[shelf][endinner]-sumcandyleft[shelf][l2]+candy[shelf][l2];
        if (intersect > 0) 
            return -1;
        totalcandy = getmaxcandybetween(shelf,l1, pl1 == endinner ? pl2:pl1, 1, 1);
    }
    return totalcandy;
} 
void solve(){
    int i, j, precsum, closest, k, pi, pj, max;
    int result[MAXL][MAXL];
    int prevresult[MAXL][MAXL];
    int finalresult = 0;
    for (i = 0; i<n; ++i) {
        precsum = 0;
        closest = -1;
        for (j = 0; j<m; ++j){
            precsum = precsum + candy[i][j];
            sumcandyleft[i][j] = precsum;
            if (candy[i][j])
                closest = j;
            closestcandyleft[i][j] = candy[i][j]? -1: closest;
        }
        closest = -1;
        for (j = m-1; j>=0; j--) {
            if (candy[i][j])
                closest = j;
            closestcandyright[i][j] = candy[i][j]? -1:closest;    
        }
    }
    for (k = 1; k<=n; ++k) {
       for (i = 0; i<countupladders[k]; ++i)
         for (j = i; j<countupladders[k]; ++j) {
            if ( k == 1)
                result[i][j] = 0;
            else {
                result[i][j] = -1;
                for (pi = 0; pi<countupladders[k-1]; ++pi)
                    for (pj = pi; pj<countupladders[k-1]; ++pj)
                      if (prevresult[pi][pj]!=-1) {
                        max = getmaxcandy(k-1, upladders[k][i], upladders[k][j], upladders[k-1][pi], upladders[k-1][pj]);
                        if (max != -1 && prevresult[pi][pj]+max > result[i][j])
                            result[i][j] = max+prevresult[pi][pj];
                      }
            }
            if (result[i][j]!=-1){
                max = k==n? 0: getmaxcandybetween(k, upladders[k][i], upladders[k][j], 1,1); //segment on shelf k
                if (result[i][j]+max > finalresult)
                    finalresult = result[i][j]+max;
            }
        }        
        for (i = 0; i<countupladders[k]; ++i)
            for (j = i; j<countupladders[k]; ++j)
                prevresult[i][j] = result[i][j];
    }
    printf("%d\n", finalresult);       
}
int main(){
    readData();
    solve();
    return 0;
}
