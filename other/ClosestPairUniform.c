#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<unistd.h>

enum{BUFSIZE = 1073741824};
enum{MAXLINE = 30        };

typedef struct {
    double x, y;
} point;
point points[100001];
char inp[BUFSIZE];
char line[30];
int pointer = 0;
int compare(const void* e1, const void* e2){
    point *p1 = (point*)e1;
    point *p2 = (point*)e2;
    return p1->x - p2->x;
}
double distance(point p1, point p2){
    double x = pow(p2.x - p1.x, 2);
    double y = pow(p2.y - p1.y, 2);
    return sqrt(x + y);
}
int buff_pointer = 0;
int buff_read = -1;
void readline(){
    int i;
    char c;
    if(buff_read<0){
        buff_read = read(0, inp, BUFSIZE);
    }
    for(i=0;i<MAXLINE;i++){
        if(buff_pointer>=BUFSIZE){
            buff_pointer=0;
            buff_read = read(0, inp, BUFSIZE);
            if(!buff_read) break;
        }
        c = inp[buff_pointer];
        buff_pointer++;
        line[i]=c;
        if(c=='\n'){
            break;
        }
    }
}
int main(){
    int n, i, j;
    point aux, aux2, res1, res2;
    double dist, daux;
    while(1){
        readline();
        sscanf(line, "%d", &n);
        if(!n) break;
        for(i=0; i<n; i++){
            readline();
            sscanf(line, "%lf %lf", &aux.x, &aux.y);
            points[i] = aux;
        }
        qsort(points, n, sizeof(point), compare);
        res1 = aux = points[0];
        res2 = aux2 = points[1];
        dist = distance(aux, aux2);
        for(i=2; i<n; i++){
            aux = points[i];
            for(j=i-1; j>=0; j--){
                aux2 = points[j];
                daux = distance(aux, aux2);
                if(daux < dist){
                    dist = daux;
                    res1 = aux2;
                    res2 = aux;
                }
                else if((aux.x - aux2.x) > dist){
                    break;
                }
            }
        }
        printf("%.2lf %.2lf %.2lf %.2lf\n", res1.x, res1.y, res2.x, res2.y);
    }
    return 0;
}
