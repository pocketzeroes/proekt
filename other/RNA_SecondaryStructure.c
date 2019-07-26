#define _GNU_SOURCE 1
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}
#define swap(a,b) do{ typeof(a) tmp; tmp = a; a = b; b = tmp; }while(0)

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}

enum{ NUMBEROFTESTCASES = 200};

int n;
char*rna;
int cg;

int dp[155][155][21];

bool complementary(char c1, char c2){
    if( c1 > c2 ) 
        swap(c1, c2);
    if( c1 == 'A' && c2 == 'U' ) return true;
    if( c1 == 'C' && c2 == 'G' ) return true;
    return false;
}
void extract(char*left, char*right, int*leftCount, int*rightCount, char*rna){
    int i;
    char*s = strdup("");
   *left = rna[0];
    for(i = 1; isdigit(rna[i]); i++)
        s = concatc(s, rna[i]);
    sscanf(s, "%d", leftCount);
    for(i = strlen(rna) - 1; i >= 0 && isdigit(rna[i]); i--);
   *right = rna[i];
    free(s);
    s = strdup("");
    for(++i; i < strlen(rna); i++)
        s = concatc(s, rna[i]);
    sscanf(s, "%d", rightCount);
}
char*decodeRLE(char*rna){
    int start, end;
    int i, j;
    for(i = 1; isdigit(rna[i]); i++);
    start = i;
    for(i = strlen(rna) - 1; isdigit(rna[i]); i--);
    end = i - 1;
    char*res = strdup("");
    for(i = start; i <= end; i++) {
        char ch = rna[i];
        char*s = strdup("");
        int cnt;
        for(j = i + 1; j <= end && isdigit(rna[j]); j++) {
            s = concatc(s, rna[j]);
        }
        sscanf(s, "%d", &cnt);
        while(cnt--)
            res = concatc(res, ch);
        i = j - 1;
    }
    return res;
}
int memo(int start, int end, int cg){
    if( start >= end ) 
        return 0;
    if( dp[start][end][cg] != -1 )
        return dp[start][end][cg];
    int res = 0;
    int i, a;
    if( complementary(rna[start], rna[end]) && (rna[start] == 'A' || rna[start] == 'U') ) {
        int res = 1 + memo(start + 1, end - 1, cg);
        return dp[start][end][cg] = res;
    }
    for(i = start + 1; i <= end; i++) {
        if( complementary(rna[start], rna[i]) ) {
            if(rna[start] == 'C' || rna[start] == 'G') {
                if( cg == 0 ) 
                    continue;
                for(a = 0; a <= cg - 1; a++) {
                    int k1 = memo(start + 1, i - 1, a);
                    int k2 = memo(i + 1, end, cg - 1 - a);
                    if( res < k1 + k2 + 1 ) 
                        res = k1 + k2 + 1;
                }   
            }
            else {
                for(a = 0; a <= cg; a++) {
                    int k1 = memo(start + 1, i - 1, a);
                    int k2 = memo(i + 1, end, cg - a);
                    if( res < k1 + k2 + 1 ) 
                        res = k1 + k2 + 1;
                }   
            }
        }
    }
    int k = memo(start + 1, end, cg);
    if( k > res ) 
        res = k;
    return dp[start][end][cg] = res;
}
int main(){
    int test;
    char left, right;
    int leftCount, rightCount;
    char*input;
    scanf("%d", &test);
    assert(test <= NUMBEROFTESTCASES);
    for(int cases=1; cases<=test; cases++){
        input=getstr();
        scanf("%d", &cg);
        assert(cg >= 0 && cg <= 20);
        extract(&left, &right, &leftCount, &rightCount, input);
        rna = decodeRLE(input);
        assert(strlen(rna) <= 50);
        int res = 0;
        if( complementary(left, right) ){
            res += min(leftCount, rightCount);
            leftCount  -= res;
            rightCount -= res;
            if( left == 'C' || left == 'G' ){
                res = min(res, cg);
                cg -= res;
            }
        }
        leftCount  = min(leftCount , 52);
        rightCount = min(rightCount, 52);
        char*s = strdup("");
        while(leftCount--)
            s = concatc(s, left);
        rna = concats(s, rna);
        while(rightCount--)
            rna = concatc(rna, right);
        n = strlen(rna);
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                for(int k = 0; k <= cg; k++)
                    dp[i][j][k] = -1;
        res += memo(0, n-1, cg);
        printf("Case %d: %d\n", cases, res);
    }
    return 0;
}
