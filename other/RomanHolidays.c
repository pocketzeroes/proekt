#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char*ones[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};
char*tens[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
char*huns[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
char*lower[999]; 
int nlower = 0;
char*upper[999]; 
int nupper = 0;

char*prepend(char*s, char*v){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", s, v);
  return ptr;
}

char*convert(long val){
    char*ans = strdup(ones[val%10]);
    val /= 10;
    ans = prepend(tens[val%10], ans); val /= 10;
    ans = prepend(huns[val%10], ans);
    return ans;
}
void insertLower(char*s){
    int loc = nlower;
    while (loc > 0 && strcmp( lower[loc-1], s)>0){
        lower[loc] = strdup(lower[loc-1]);
        loc--;
    }
    lower[loc] = strdup(s);
    nlower++;
}
void insertUpper(char*s){
    int loc = nupper;
    while (loc > 0 && strcmp(upper[loc-1], s)<0) {
        upper[loc] = strdup(upper[loc-1]);
        loc--;
    }
    upper[loc] = strdup(s);
    nupper++;
}
int find(char* s, char**a, int n){
    for(int i=0; i<n; i++)
        if(strcmp(a[i], s)==0)
            return i;
    return -1;       
}
int main(){
    for(int i=1; i<1000; i++) {
        char*s = convert(i);
        if(s[0] < 'V')
            insertLower(s);
        else
            insertUpper(s);
    }
    int n;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        long val;
        scanf("%ld", &val);
        int numM = val/1000;
        char*s = convert(val % 1000);
        if(strcmp(s, "V")<0){
            int loc = find(s, lower, nlower)+1;
            printf("%d\n", numM*(nlower+1) + loc);
        }
        else{
            int loc = find(s, upper, nupper) + 1;
            printf("%d\n", -(numM*nupper + loc) );
        }
    }
    return 0;
}
