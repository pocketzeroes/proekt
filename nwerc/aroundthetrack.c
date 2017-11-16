#pragma GCC diagnostic ignored "-Wunused-result"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

typedef long long ll;
double min(double a, double b){return a<b?a:b;}
double max(double a, double b){return a>b?a:b;}

enum{ N = 50};
#define infty 1e9
int X[2*N+1], Y[2*N+1];
double Dis[2*N+1][2*N+1];
bool Seen[2*N+1];

ll area2 (int a, int b, int c)
{
    return X[a]*Y[b] - X[b]*Y[a] + X[b]*Y[c] - X[c]*Y[b] + X[c]*Y[a] - X[a]*Y[c];
}
bool intersect (int a, int b, int c, int d)
{
    ll a1 = area2(a,b,c), a2 = area2(a,b,d), a3 = area2(a,c,d), a4 = area2(b,c,d);
    if (a1 || a2 || a3 || a4)
    {
        ll p1 = a1*a2, p2 = a3*a4;
        return p1 <= 0 && p2 <= 0 && (p1 < 0 || p2 < 0);
    }
    int *Z = (X[a1] == X[a2] ? Y : X);
    return (Z[c]-Z[a])*(Z[c]-Z[b]) < 0 || (Z[d]-Z[a])*(Z[d]-Z[b]) < 0;
}
int main()
{
    int n1, n2, i, j, k, q, m, r, s;
    double d;
    bool intersection, inside, outside, crossfinish;
    scanf("%d", &n1);
    for (i = 0; i < n1; i++)
        scanf("%d %d", &X[i], &Y[i]);
    scanf("%d", &n2);
    for (i = 0; i < n2; i++)
        scanf("%d %d", &X[n1+i], &Y[n1+i]);
    r = 0;
    for (i = 1; i < n1; i++)
        if (X[i] > X[r] || (X[i] == X[r] && Y[i] < Y[r]))
            r = i;
    s = (r+1)%n1;
    m = n1+n2;
    for (i = 0; i <= m; i++)
        for (j = 0; j <= m; j++)
            Dis[i][j] = infty;
    for (i = 1; i < m; i++)
        for (j = 0; j < i; j++)
        {
            intersection = inside = outside = crossfinish = false;
            for (k = 0; k < m; k++)
            {
                q = (k == n1-1 ? 0 : k == m-1 ? n1 : k+1);
                if (intersect(i,j,k,q))
                    intersection = true;
            }
            if (area2(i,r,s)*area2(j,r,s) <= 0 && (area2(i,j,r)*area2(i,r,s) > 0 || area2(i,j,r)*area2(j,r,s) < 0))
                crossfinish = true;
            if (i < n1 && j < n1)
            {
                k = (i == n1-1 ? 0 : i+1);
                q = (i == 0 ? n1-1 : i-1);
                if ((area2(q,i,k) >= 0 && area2(i,k,j) > 0 && area2(i,j,q) > 0) || (area2(q,i,k) < 0 && (area2(i,k,j) > 0 || area2(i,j,q) > 0)))
                    inside = true;
            }
            if (i >= n1 && j >= n1)
            {
                k = (i == m-1 ? n1 : i+1);
                q = (i == n1 ? m-1 : i-1);
                if ((area2(q,i,k) <= 0 && area2(i,k,j) < 0 && area2(i,j,q) < 0) || (area2(q,i,k) > 0 && (area2(i,k,j) < 0 || area2(i,j,q) < 0)))
                    outside = true;
            }
            if (!intersection && !inside && !outside && !crossfinish)
            {
                k = (i == r && area2(r,s,j) > 0 ? m : i);
                q = (j == r && area2(r,s,i) > 0 ? m : j);
                Dis[k][q] = Dis[q][k] = sqrt((X[i]-X[j])*(X[i]-X[j]) + (Y[i]-Y[j])*(Y[i]-Y[j]));
            }
        }
    Dis[r][r] = 0;
    memset(Seen, false, sizeof(Seen));
    while (true)
    {
        j = -1;
        d = infty;
        for (i = 0; i <= m; i++)
            if (!Seen[i] && Dis[r][i] < d)
                d = Dis[r][j = i];
        if (j == -1)
        {
            printf("Fail!\n");
            return 0;
        }
        if (j == m)
            break;
        Seen[j] = true;
        for (i = 0; i <= m; i++)
            Dis[r][i] = min(Dis[r][i], Dis[r][j] + Dis[j][i]);
    }
    printf("%lf\n", Dis[r][m]);
    return 0;
}




