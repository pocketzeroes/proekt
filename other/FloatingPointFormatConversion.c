#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

typedef unsigned long ul;

ul FormatConvert(ul GouldFP){
    ul sign, expon, mantissa, res;
    int expv;
    sign = GouldFP & 0x80000000;
    expon = (GouldFP & 0x7f000000) >> 24;
    expv = expon - 64;
    mantissa = GouldFP & 0xffffff;
    if(mantissa == 0)
        return 0;
    expv *= 4;
    while((mantissa & 0x800000) == 0){
        mantissa <<= 1;
        expv--;
    }
    expv--;
    if(expv > 127)
        res = sign | 0x7f800000;
    else if(expv < -149)
        res = sign;
    else if(expv >= -126){
        expon = expv + 127;
        expon <<= 23;
        res = sign | expon | (mantissa & 0x7fffff);
    }
    else {
        while(expv < -126) {
            expv++;
            mantissa >>= 1;
        }
        expon = 0;
        res = sign | expon | (mantissa & 0x7fffff);
    }
    return res;
}
int main(){
    int nprob, curprob, index;
    ul inval, res;
    if(scanf("%d", &nprob) != 1){
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    for(curprob = 1; curprob <= nprob ; curprob++){
        if(scanf("%d %lx", &index, &inval) != 2){
            fprintf(stderr, "scan failed on problem data problem index %d\n", curprob);
            return -6;
        }
        res = FormatConvert(inval);
        printf("%d %08lX\n", curprob, res);
    }
    return 0;
}
