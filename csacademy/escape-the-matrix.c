#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

int r,c;
char a  [510][510];
bool vis[510][510];

char check (int i, int j){
    if (vis[i][j])
        return a[i][j];
    vis[i][j]=1;
    int ci=i , cj=j;
    if (a[i][j]=='D') ci++;
    if (a[i][j]=='U') ci--;
    if (a[i][j]=='R') cj++;
    if (a[i][j]=='L') cj--;
    if (ci>=r || ci<0 || cj>=c || cj<0)
        return a[i][j]='1';
    char x = check (ci,cj);
    if (x=='1')
        return a[i][j]='1';
    return a[i][j];
}
int main(){
    scanf("%d %d", &r, &c);
    for (int i=0;i<r;i++)
        scanf("%s",a[i]);
    for (int i=0;i<r;i++)
        for (int j=0;j<c;j++)
            if (!vis[i][j])
                check (i,j);
    int x=0;          
    for (int i=0;i<r;i++)
        for (int j=0;j<c;j++)
            if (a[i][j]=='1')
                x++;
    printf("%d\n", x);
    return 0;
}
