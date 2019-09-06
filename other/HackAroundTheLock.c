#include<stdio.h>
#include<stdlib.h>
#include<string.h>
enum{ MAXK    = 7,
      MAXSUMN = 12000000};
int start;
int digcnt,n;
int p10     [MAXK+2];
int bplen   [MAXK+1], 
    eplen   [MAXK+1];
int bigarray[3*MAXSUMN];
int *begpath[MAXK+1];
int *endpath[MAXK+1];
int *cycle  [MAXK+1];


void copy_with_prefix(int cnt, int *to, int *from, int rev, int digcnt, int prefix){
    int i;
    for(i=0;i<cnt;i++){
        if(!rev) to[i] = from[i]; else to[i] = from[cnt-1-i];
        to[i] += p10[digcnt]*prefix;
    }
}
void copy_with_suffix(int cnt, int *to, int *from, int rev, int suffix){
    int i;
    for(i=0;i<cnt;i++){
        if(!rev) to[i] = from[i]; else to[i] = from[cnt-1-i];
        to[i] = to[i]*10 + suffix;
    }
}
void constr_begpath(int k){
    int i;
    int *to;
    if(k==1){
        for(i=1;i<10;i++)
            begpath[k][i-1] = i;
        return;
    }
    to = begpath[k];
    for(i=0;i<10;i++){
        copy_with_prefix(bplen[k-1], to, begpath[k-1], (i&1), k-1, i);
        to += bplen[k-1];
    }
}
void constr_endpath(int k){
    int i;
    int *to;
    if(k==1){
        endpath[k][0] = 0;
        return;
    }
    to = endpath[k];
    for(i=0;i<10;i++){
        copy_with_prefix(eplen[k-1], to, endpath[k-1], (i&1), k-1, i);
        to += eplen[k-1];
    }
}
void constr_ham_cycle(int k){
    int i;
    int *to, *b, *e;
    to = cycle[k]; b = begpath[k]; e = endpath[k];
    memcpy(to, b, bplen[k]*sizeof(b[0]));
    to += bplen[k];
    for(i=0;i<eplen[k];i++) to[i] = e[eplen[k]-1-i];
}
int main(){
    int i;
    char tmps[MAXK+5];
    int *res;
    char pfstring[10]="%0xd ";
    p10[0]=1;
    for(i=1;i<=MAXK;i++) 
        p10[i] = 10*p10[i-1];
    for(i=1;i<=MAXK;i++) { bplen[i] = 9*p10[i-1]; eplen[i] = p10[i-1]; }
    begpath[1] = bigarray;
    for(i=2;i<=MAXK;i++)
        begpath[i] = begpath[i-1]+bplen[i-1];
    endpath[1] = begpath[MAXK]+bplen[MAXK];
    for(i=2;i<=MAXK;i++)
        endpath[i] = endpath[i-1]+eplen[i-1];
    cycle[1] = endpath[MAXK]+eplen[MAXK];
    for(i=2;i<=MAXK;i++)
        cycle[i] = cycle[i-1]+p10[i-1];
    for(i=1;i<=MAXK;i++)
        constr_begpath(i);
    for(i=1;i<=MAXK;i++)
        constr_endpath(i);
    for(i=2;i<=MAXK;i++)
        constr_ham_cycle(i);
    while(1){
        tmps[0]='\0';
        scanf(" %s ", tmps);
        if(tmps[0]<'0' || tmps[0]>'9')
            break;
        digcnt=0;
        start = 0;
        for(i=0; tmps[i]>='0' && tmps[i]<='9'; i++){
            start = start*10 + (tmps[i]-'0');
            digcnt++;
        }
        n = p10[digcnt];
        pfstring[2] = digcnt+'0';
        if(digcnt==1){
            if(start<5){
                printf("%d\n", 9+start);
                for(start--; start>=0; start--) printf("%01d ", start);
                for(start=1; start<10; start++) printf("%01d ", start);
            }
            else{
                printf("%d\n", 9+(10-start)-1);
                for(start++; start<10; start++) printf("%01d ", start);
                for(start=8; start>=0; start--) printf("%01d ", start);
            }
            printf("\n");
            continue;
        }
        res = cycle[digcnt];
        printf("%d\n",n-1);
        for(i=0;i<n;i++)
            if(res[i]==start)
                break;
        i = (i+1)%n;
        while(res[i]!=start){
            printf(pfstring, res[i]);
            i=(i+1)%n;
        }
        printf("\n");
    }
    return 0;
}
