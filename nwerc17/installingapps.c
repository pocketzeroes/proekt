#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

enum{ nmax = 500  };
enum{ cmax = 10000};

typedef struct{
    int d, s, id;
}app;
app App[nmax];

app newApp(int d0, int s0, int id0){
    app rez;
    rez.d = d0;
    rez.s = s0;
    rez.id = id0;
    return rez;
}

int Size[nmax+1], Last[nmax+1], Prev[nmax+1][nmax+1], Order[nmax+1];

int cmp(const void*pa, const void*pb){
    app*A=(app*)pa;
    app*B=(app*)pb;
    return(A->d - A->s > B->d - B->s)?-1:1;
}
int main(){
    int n, c, i, d, s, k, m;
    scanf("%d %d", &n, &c);
    for (i = 0; i < n; i++){
        scanf("%d %d", &d, &s);
        App[i] = newApp(d, s, i+1);
    }
    qsort(App, n, sizeof(app), cmp);
    m = 0;
    Size[0] = 0;
    for (i = 0; i < n; i++){
        for (k = m; k >= 0; k--)
            if (Size[k] + App[i].d <= c && Size[k] + App[i].s <= c && (k == m || Size[k+1] > Size[k] + App[i].s)){
                Size[k+1] = Size[k] + App[i].s;
                Last[k+1] = i;
                Prev[k+1][i] = Last[k];
                if (k == m)
                    m++;
            }
    }
    i = Last[m];
    for (k = m; k > 0; k--){
        Order[k-1] = i;
        i = Prev[k][i];
    }
    printf("%d\n", m);
    for (k = 0; k < m; k++)
        printf("%d%c", App[Order[k]].id, k<m-1?' ':'\n');
    return 0;
}
