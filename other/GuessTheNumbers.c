#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
#include<ctype.h>

void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void rev(int*s, int l, int r){
    while(l<r)
        swap(s, l++, r--);
}
int b_search(int*s,int l,int r,int key){
    int index = -1;
    while(l<=r){
        int mid = l+(r-l)/2;
        if(s[mid]<=key)
            r=mid-1;
        else{
            l=mid+1;
            if(index = -1 || s[index]<=s[mid])
                index = mid;
        }
    }
    return index;
}
bool next_permutation(int*s, int sl){
    int len = sl, i=len-2;
    while(i>=0 && s[i]>=s[i+1])
       --i;
    if(i<0)
        return false;
    else{
        int index=b_search(s, i+1, len-1, s[i]);
        swap(s, i, index);
        rev(s, i+1, len-1);
        return true;
    }
}

int cmp(const void * a, const void * b){
  return ( *(int*)a - *(int*)b );
}
char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ MAXVAR = 5};
typedef struct expr{
  char         op;
  int*         v;
  struct expr* izq;
  struct expr* der;
} expr;
int values[MAXVAR];
char*expression;

expr*newexpr(){
  return calloc(1, sizeof(expr));
}
expr*parseExpression(char*expression, int*pos, int*nvar){
  expr*ret = NULL;
  if( expression[*pos] == '(' ){
    ret = newexpr();
    (*pos)++;
    ret->izq = parseExpression( expression, pos, nvar);
    ret->op = expression[*pos];
    (*pos)++;
    ret->der = parseExpression( expression, pos, nvar);
    (*pos)++;
  }
  else if (islower(expression[*pos])){
    ret = newexpr();
    ret->v = values +  *nvar;
    ret->izq = ret->der = NULL;
    (*pos)++;
    (*nvar)++;
  }
  else{
    assert(!"Invalid Expression");
  }
  return ret;
}
int evalExpression( expr* e ){
  int res = -1;
  if( (e->izq == NULL) && (e->der == NULL) ){
    res = *(e->v);
  }
  else{
    int v1 = evalExpression(e->izq);
    int v2 = evalExpression(e->der);
    switch (e->op){
      case '+': res = v1 + v2; break;
      case '-': res = v1 - v2; break;
      case '*': res = v1 * v2; break;
    }
  }
  return res;
}
void freeExpr(expr*e){
  if( e->izq != NULL )
    freeExpr(e->izq);
  if( e->der != NULL )
    freeExpr(e->der);
  free(e);
  e=NULL;
}
int main(){
  expr*e;
  int pos = 0, nvar = 0;
  int n, result, act;
  bool possible;
  while(1){
    scanf("%d", &n);
    for( int i = 0; i < n; ++i ){
      scanf("%d", &values[i]);
    }
    qsort(values, n, sizeof(int), cmp);
    scanf("%d", &result);
    if( (n == 0) && (result == 0) )
      break;
    expression = getstr();
    pos = nvar = 0;
    e = parseExpression(expression, &pos, &nvar);
    possible = false;
    do{
      act = evalExpression(e);
      if (act == result){
        possible = true;
      }
    }
    while( !possible && next_permutation(values, n));
    if (possible)
      puts("YES");
    else
      puts("NO");
    freeExpr(e);
  }
  return 0;
}
