#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

struct paris
{
    int a;
    int b;
} mas[100000];
int degree[100001];
long long neighboursum[100001];
int rinda[100000];
int subtree[100001];
int place[100001];
int fatchild[100001];
int order[100000];
int place2[100001];
int group[100002];
int groupSize[100002];
int counters[100002];
int n;
int min(int a, int b){
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}
int main(){
    scanf("%d", &n);
    for (int i = 0; i < n - 1; i++)
    {
        scanf("%d %d", &mas[i].a, &mas[i].b);
        degree[mas[i].a]++;
        degree[mas[i].b]++;
        neighboursum[mas[i].a] += mas[i].b;
        neighboursum[mas[i].b] += mas[i].a;
    }
    int prieksa = 0;
    int aste = 0;
    for (int i = 1; i <= n; i++)
    {
        subtree[i] = 1;
        place[i] = i;
        if (degree[i] == 1)
        {
            rinda[prieksa] = i;
            prieksa++;
        }
    }
    while (prieksa > aste)
    {
        int x = rinda[aste];
        aste++;
        int y = neighboursum[x];
        if (y > 0)
        {
            if (fatchild[y] == 0 || subtree[fatchild[y]] < subtree[x])
            {
                fatchild[y] = x;
            }
            subtree[y] += subtree[x];
            degree[y]--;
            neighboursum[y] -= x;
            if (degree[y] == 1)
            {
                rinda[prieksa] = y;
                prieksa++;
            }
        }
    }
    long long minDistance = 0;
    long long maxDistance = 0;
    for (int i = 0; i < n; i++)
    {
        int x = rinda[i];
        if (place[x] == x)
        {
            int y = neighboursum[x];
            if (y > 0)
            {
                place[x] = place[y];
                place[y] = x;
                minDistance += 2;
            }
            else
            {
                int j = i;
                int z;
                do
                {
                    j--;
                    z = rinda[j];
                }
                while (j >= 0 && neighboursum[z] != x);
                place[x] = place[z];
                place[z] = x;
                minDistance += 2;
            }
        }
    }
    for (int i = 1; i <= n; i++)
    {
        maxDistance += 2 * min(subtree[i], n - subtree[i]);
    }
    printf("%lld %lld\n", minDistance, maxDistance);
    for (int i = 1; i <= n; i++)
    {
        printf("%d", place[i]);
        if (i < n)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }
    int c = 1;
    int cc = 1;
    do
    {
        c = cc;
        if (subtree[c] < n / 2 + n % 2)
        {
            cc = neighboursum[c];
        }
        else if (subtree[c] > n / 2)
        {
            if (fatchild[c] != 0 && subtree[fatchild[c]] > n / 2)
            {
                cc = fatchild[c];
            }
        }
    }
    while (cc != c);
    int nextGroup = 2;
    for (int i = n-1; i>=0 ; i--)
    {
        int x = rinda[i];
        if ((x == c) || (neighboursum[x] == c))
        {
            group[x] = nextGroup;
            nextGroup++;
        }
        else if (neighboursum[x] > 0)
        {
            group[x] = group[neighboursum[x]];
        }
        else
        {
            group[x] = 1;
        }
        groupSize[group[x]]++;
    }
    for (int i = 1; i < nextGroup; i++)
    {
        groupSize[i] += groupSize[i-1];
    }
    for (int i = 1; i <= n; i++)
    {
        order[groupSize[group[i]-1]+counters[group[i]]] = i;
        counters[group[i]]++;
    }
    for (int i = 0; i < n; i++)
    {
        place2[order[i]] = order[(i+ n / 2) % n];
    }
    for (int i = 1; i <= n; i++)
    {
        printf("%d", place2[i]);
        if (i < n)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }
    return 0;
}
