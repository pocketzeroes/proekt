#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
void backtrack();
void replace(char *s, char a, char b);
int check();

char x[110], y[110];
int a, b, c, flag;

int main() {
  while (1) {
    x[0] = y[0] = '+'; a = 1;
    do x[a] = y[a] = getchar(); while (isspace(x[a]));
    if ( x[a]<'A' || x[a]>'Z') break;
    for ( ;x[a]>='A' && x[a]<='Z';) {
      a++; x[a] = y[a] = getchar();
    }
    --a; b=a+2;
    for (x[b]=y[b]=getchar(); x[b]>='A' && x[b]<='Z'; ) {
      ++b; x[b] = y[b] = getchar();
    }
    --b; c=b+2;
    for (x[c]=y[c]=getchar(); x[c]>='A' && x[b]<='c'; ) {
      ++c; x[c] = y[c] = getchar();
    }
    x[c] = y[c] = '\0'; --c;

    flag = 0; backtrack(1);
    if (!flag) printf("impossible\n");
    else printf("%s\n", y+1);
  }
  return 0;
}

void backtrack() {
  char ch, d;
  for(ch='A'; ch<='Z' && strchr(y, ch)==NULL; ++ch) ;
  if (ch > 'Z') { flag=1; return; }

  for(d='0'; d<='9'; ++d) {
    if (strchr(y,d) != NULL) continue;
    replace(y, ch, d);
    if (check()) backtrack();
    if (flag) return;
    replace(y, d, ch);
  }
}

void replace(char *s, char a, char b) {
  for(; *s!='\0'; ++s)
    if (*s==a) *s=b;
}

int check() {
  int i=a, j=b, k=c, cr=0;
  for(;;) {
    if (isalpha(y[i]) || isalpha(y[j]) || isalpha(y[k])) return 1;
    int a1 = ((y[i]=='+') ? 0 : (y[i]-'0'));
    int b1 = ((y[j]=='+') ? 0 : (y[j]-'0'));
    int c1 = ((y[k]=='=') ? 0 : (y[k]-'0'));
    if (c1 != (a1+b1+cr) % 10) return 0;
    cr  = (a1+b1+cr) / 10;
    if (y[i]!='+') i--;
    if (y[j]!='+') j--;
    if (y[k]!='=') k--;
    if (y[i]=='+' && y[j]=='+' && y[k]=='=') break;
  }
  if (cr>0 || y[i+1]=='0' || y[j+1]=='0' || y[k+1]=='0') return 0;

  return 1;
}
