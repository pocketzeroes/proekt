#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>

int steps[7];


int FindSpiral(int index, int x, int y){
    if(y > x) {
        printf("%d 2 %d %d\n", index, x, y);
        steps[0] = 2;
        steps[1] = x;
        steps[2] = y;
    }
    else if (y >= 4) {
        printf("%d 6 1 2 3 %d %d %d\n", index, x + 5 - y, x+2, x+3);
        steps[0] = 6;
        steps[1] = 1;
        steps[2] = 2;
        steps[3] = 3;
        steps[4] = x + 5 - y;
        steps[5] = x+2;
        steps[6] = x+3;
    } 
    else {
        printf("%d NO PATH\n", index);
        steps[0] = 0;
    }
    return steps[0];
}
int CheckSpiral(int x, int y){
    int xi, yi;
    xi = yi = 0;
    if(steps[0] == 0) {
        return 0;
    }
    else if(steps[0] == 2) {
        xi += steps[1];
        yi += steps[2];
    }
    else if(steps[0] == 6) {
        xi += steps[1];
        yi += steps[2];
        xi -= steps[3];
        yi -= steps[4];
        xi += steps[5];
        yi += steps[6];
    }
    else {
        printf("steps %d\n", steps[0]);
        return -1;
    }
    if((xi != x) || (yi != y)) {
        printf("(%d, %d) != (%d, %d)\n", xi, yi, x, y);
        return -2;
    }
    return 0;
}
char inbuf[256];

int main(int argc, char **argv){
    int nprob, curprob, index, x, y;
    if(fgets(&(inbuf[0]), 255, stdin) == NULL){
        fprintf(stderr, "Read failed on problem and star count\n");
        return -1;
    }
    if(sscanf(&(inbuf[0]), "%d", &nprob) != 1){
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    for(curprob = 1; curprob <= nprob ; curprob++){
        if(fgets(&(inbuf[0]), 255, stdin) == NULL){
            fprintf(stderr, "Read failed on problem data problem index  %d \n", curprob);
            return -3;
        }
        if(sscanf(&(inbuf[0]), "%d %d %d", &index, &x, &y) != 3){
            fprintf(stderr, "scan failed on problem data problem index %d\n", curprob);
            return -6;
        }
        if(curprob != index) {
            fprintf(stderr, "problem index %d not = expected %d\n", index, curprob);
            return -7;
        }
        FindSpiral(index, x, y);
        if(CheckSpiral(x, y) != 0) {
            printf("error\n");
        }
    }
    return 0;
}
