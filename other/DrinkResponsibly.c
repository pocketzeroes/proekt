#include<math.h>
#include<stdio.h>
#include<string.h>

enum{ maxd = 110 };
enum{ maxc = 1010};
enum{ maxu = 1210};

typedef struct beer{
    char name[255];
    int unit6;
    int cost; 
}beer;
int readcost(){
    int i,f;
    scanf("%d.%d",&i,&f);
    return 100*i+f;
}
int main(){
    int m, u, d, f;
    beer beers[maxd];
    int reach[maxc][maxu];
    int used[maxd];
    m = readcost();
    scanf("%d.%d %d\n",&u,&f,&d);
    if ( f%5!=0 ){
        printf("IMPOSSIBLE\n");
        return 0;
    }
    u = 6*u+3*(f/5);
//  fprintf(stderr,"read m=%d u=%d d=%d\n",m,u,d);
    for(int i=0; i<d; i++){
        int perc, frac;
        scanf("%s %d 1/%d ",beers[i].name,&perc,&frac);
        beers[i].unit6 = perc*6/frac;
        beers[i].cost = readcost();
    }
    for(int i=0; i<maxc; i++)
        for(int j=0; j<maxu; j++)
            reach[i][j] = -2;
    reach[0][0] = -1;
    for(int i=0; i<=m; i++) {
        for(int j=0; j<=u; j++) {
            if ( reach[i][j]==-2 )
                continue;
            for(int b=0; b<d; b++) {
                if ( i+beers[b].cost<=m && j+beers[b].unit6<=u ) {
                    reach[i+beers[b].cost][j+beers[b].unit6] = b;
                }
            }
        }
    }
    if ( reach[m][u]==-2 ) {
        printf("IMPOSSIBLE\n");
        return 0;
    }
    for(int i=0; i<d; i++)
        used[i] = 0;
    while ( !(m==0 && u==0) ) {
        int b = reach[m][u];
        if ( b==-2 ) {
            fprintf(stderr, "error: b=-2 at %d,%d\n",m,u);
            return 1;
        }
//      fprintf(stderr,"using beer %d: %s\n",b,beers[b].name);
        used[b]++;
        m -= beers[b].cost;
        u -= beers[b].unit6;
    }
    for(int i=0; i<d; i++) {
        if ( used[i]>0 ) {
            printf("%s %d\n",beers[i].name,used[i]);
        }
    }
    return 0;
}
