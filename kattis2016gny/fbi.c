#include <stdio.h>
#include <ctype.h>

int alphaLookup[ 26] ={ 10, 8, 11, 12, 13, 14, 11, 15, 1, 16, 17, 18, 19, 20, 0, 21, 0, 22, 5, 23, 24, 24, 25, 26, 24, 2 };
int factors    [  8] = {2, 4, 5, 7, 8, 10, 11, 13};
int UCNdigits  [  9];
char inbuf     [256];

int parseInput(char *pb, int inprob){
    int i, probnum = 0;
    char c;
    while(*pb != 0) {
        if(!isspace(*pb))
            break;
        pb++;
    }
    if(*pb == 0) {
        printf("parseInput: unexpect end of string  on prob num %d\n", inprob);
        return -1;
    }
    while(*pb != 0) {
        if(!isdigit(*pb))
            break;
        probnum = (probnum*10) + (*pb - '0');
        pb++;
    }
    if(*pb == 0) {
        printf("parseInput: unexpect end of string  on prob num %d\n", inprob);
        return -2;
    }
    while(*pb != 0) {
        if(!isspace(*pb))
            break;
        pb++;
    }
    if(*pb == 0) {
        printf("parseInput: unexpect end of string  on prob num %d\n", inprob);
        return -3;
    }
    for(i = 0; i < 9 ; i++) {
        c = *pb++;
        if((c >= '0') && (c <= '9')) {
            UCNdigits[i] = c - '0';
        }
        else if((c >= 'A') && (c <= 'Z')) {
            UCNdigits[i] = alphaLookup[c - 'A'];
        }
        else {
            printf("parseInput: bad digit char %c[0x%02x] prob num %d\n", c, c, inprob);
            return -4;
        }
    }
    return probnum;
}
int checkDigit(){
    int i, ret = 0;
    for(i = 0; i < 8 ; i++) {
        ret += UCNdigits[i]*factors[i];
    }
    ret = (ret % 27);
    return ret;
}
int main(){
    int i, nprob, curprob, index, ret;
    unsigned long low, high;
    if(fgets(&(inbuf[0]), 255, stdin) == NULL){
        fprintf(stderr, "Read failed on problem count\n");
        return -1;
    }
    if(sscanf(&(inbuf[0]), "%d", &nprob) != 1){
        fprintf(stderr, "Scan failed on problem count\n");
        return -2;
    }
    for(curprob = 1; curprob <= nprob ; curprob++){
        if(fgets(&(inbuf[0]), 255, stdin) == NULL){
            fprintf(stderr, "Read failed on problem %d header\n", curprob);
            return -3;
        }
        if((index = parseInput(&(inbuf[0]), curprob)) < 0){
            return index;
        }
        if(index != curprob){
            fprintf(stderr, "problem index %d not = expected problem %d\n",
                index, curprob);
            return -7;
        }
        ret = checkDigit();
        if(ret != UCNdigits[8]) {
            printf("%d Invalid\n", curprob);
        }
        else {
            high = low = 0;
            for(i = 0; i < 8 ; i++) {
                low = (low *27) + UCNdigits[i];
                high = (high *27) + low/100000000;
                low = low%100000000;
            }
            printf("%d %d%08d\n", curprob, high, low);
        }
    }
    return 0;
}
