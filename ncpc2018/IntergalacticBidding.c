#include <stdio.h>
#include <stdlib.h>

enum{ MAXN = 1000};
enum{ MAXD = 1000};

typedef struct _bint_{
  int len;
  char dig[MAXD];
  char nam[22];
}bint;
bint b[MAXN];
bint s;
int n;
int win[MAXN];
int nbr = 0;

void readint(bint* t){
  char c;
  scanf("%c",&c);
  t->len = 0;
  while (c!='\n') {
    if (c>='0' && c<='9')
      t->dig[t->len++] = c-'0';
    scanf("%c",&c);  
  }
}
int cmp(const void* a, const void* b){
  bint* ba = (bint*)a;
  bint* bb = (bint*)b;
  if (ba->len>bb->len) return -1;
  if (ba->len<bb->len) return 1;
  int c = 0;
  while (c<ba->len && ba->dig[c]==bb->dig[c]) c++;
  if (c==ba->len) return 0;
  if (ba->dig[c]>bb->dig[c]) return -1;
  return 1;
}
void sub(bint* a, bint* b){
  int i;
  int d = a->len - b->len;
  int rem = 0;
  for (i = b->len-1; i >= 0; i--) {
    a->dig[i+d] -= b->dig[i] + rem;
    if (a->dig[i+d]<0) {
      a->dig[i+d] += 10;
      rem = 1;
    }
    else
      rem = 0;
  }
  d--;
  while (rem) {
   a->dig[d] -= rem;
    if (a->dig[d]<0) {
      a->dig[d] += 10;
      rem = 1;
    }
    else
      rem = 0;
    d--;
  }
  d = 0;
  while (d < a->len && a->dig[d]==0)
    d++;
  for (i = d; i < a->len; i++)
    a->dig[i-d] = a->dig[i];
  a->len -= d;  
}
int main(){
  int i;
  scanf("%d",&n);
  readint(&s);
  for (i = 0; i < n; i++) {
    scanf("%s",b[i].nam);
    readint(&b[i]);
  }
  qsort(b, n, sizeof(bint), cmp);
  for (i = 0; i < n; i++) {
    if (cmp(&s, &b[i])<= 0) {
      sub(&s, &b[i]);
      win[nbr++]=i;
    }
  }
  if (s.len==0) {
    printf("%d\n",nbr);
    for (i = 0; i < nbr; i++) {
      printf("%s\n", b[win[i]].nam);
    }
  }
  else
    printf("0\n");
  return 0;
}

