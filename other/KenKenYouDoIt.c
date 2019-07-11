#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int n, m, t, ans, x[10], y[10], ux[10][10], uy[10][10];
ll mxmul[11];
char op;

void dfsadd(int idx, int sum){
    if(sum >= t || (t-sum) > (m-idx)*n || (t-sum) < (m-idx))
        return;
    if(idx == m-1) {
        sum = t - sum;
        if(!ux[ x[idx] ][sum] && !uy[ y[idx] ][sum])
            ans++;
        return;
    }
    for(int i=1;i<=n;i++){
        if(ux[ x[idx] ][i] || uy[ y[idx] ][i])
            continue;
        ux[ x[idx] ][i] = uy[ y[idx] ][i] = 1;
        dfsadd(idx+1, sum+i);
        ux[ x[idx] ][i] = uy[ y[idx] ][i] = 0;
    }
}
void dfsmul(int idx, int sum){
    if(sum > t || t%sum || t/sum > mxmul[m-idx])
        return;
    if(idx == m-1){
        sum = t / sum;
        if(!ux[ x[idx] ][sum] && !uy[ y[idx] ][sum])
            ans++;
        return;
    }
    for(int i=1;i<=n;i++){
        if(ux[ x[idx] ][i] || uy[ y[idx] ][i])
            continue;
        ux[ x[idx] ][i] = uy[ y[idx] ][i] = 1;
        dfsmul(idx+1, sum*i);
        ux[ x[idx] ][i] = uy[ y[idx] ][i] = 0;
    }
}
int main(){
    scanf("%d %d %d %c", &n, &m, &t, &op);
    for(int i=0;i<m;i++)
        scanf("%d %d", &x[i], &y[i]);
    if(op == '-') {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(i==j)
                    continue;
                else if(abs(i-j) == t)
                    ans++;
    }
    else if(op == '/') {
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                if(j%i==0 && j/i==t)
                    ans+=2;
    }
    else if(op == '+') {
       dfsadd(0, 0);
    }
    else {
        mxmul[0] = 1;
        for(int i=1;i<=m;i++)
            mxmul[i] = mxmul[i-1] * n;
        dfsmul(0, 1);
    }
    printf("%d\n", ans);
    return 0;
}
