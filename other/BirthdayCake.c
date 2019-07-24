#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
int mp[55][55];

typedef struct{
    int x,y;
}node;
node p[55];
typedef struct{
    int a,b,c;
}nodee;
nodee qw[55];
double r;
int ok(int a,int b,int c,int d,int e,int f){
    if(a*e == b*d) 
        return 0;
    double x = ((double)(b*f) - (double)(c*e)) / ((double)(a*e) - (double)(b*d));
    double y = ((double)(a*f) - (double)(c*d)) / ((double)(b*d) - (double)(a*e));
    if(x*x + y*y <= (double)(r*r)) 
        return 1;
    else
        return 0;
}
int main(){
    int n,m;
    scanf("%d %d %lf", &n, &m, &r);
    for(int i = 1;i <= n;i++)
        scanf("%d %d",&p[i].x,&p[i].y);
    memset(mp, 0, sizeof(mp));
    for(int k = 1;k <= m;k++){
        scanf("%d %d %d", &qw[k].a, &qw[k].b, &qw[k].c);
        int f = 0;
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(j==i)
                    continue;
                int x1 = p[i].x * qw[k].a + p[i].y * qw[k].b + qw[k].c;
                int x2 = p[j].x * qw[k].a + p[j].y * qw[k].b + qw[k].c;
                if(x1 * x2 <= 0)
                    mp[i][j] = mp[j][i] = 1;
            }
        }
    }
    int qwe = m+1;
    for(int i = 1; i <= m; i++)
        for(int j = i+1; j <= m; j++)
            if(ok(qw[i].a,qw[i].b,qw[i].c,qw[j].a,qw[j].b,qw[j].c)) 
                qwe++;
    if(qwe != n)
        printf("no\n");
    else{
        for(int i =1 ;i <= n;i++){
            for(int j = 1;j <= n;j++){
                if(i==j) 
                    continue;
                if(mp[i][j] == 0){
                    printf("no\n");
                    return 0;
                }
            }
        }
        printf("yes\n");
    }
    return 0;
}
