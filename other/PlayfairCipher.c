#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<assert.h>

int pos[30], 
   grid[30];

int val(int c){ 
  if (!islower(c))
    return 0;
  int r = c - 'a' + 1;
  if (c > 'q')
    --r;
  return r;
}
int unval(int c) {
  int r = c + 'A' - 1;
  if (r >= 'Q')
    ++r;
  return r;
}
int shiftr(int p){
  if ((p+1)/5 != p/5)
    p -= 5;
  return grid[p+1];
}
int shiftd(int p){
  return grid[(p+5) % 25];
}
int main(){
  char line[2000];
  memset(pos, -1, sizeof(pos));
  fgets(line, 1500, stdin);
  assert(strlen(line) <= 1001 && line[strlen(line)-1] == '\n');
  int at = 0;
  for (char *s = line; *s; ++s)
    if (val(*s) && pos[val(*s)] == -1) {
      grid[at] = unval(val(*s));
      pos[val(*s)] = at++;
    }
  for (int x = 1; x <= 25; ++x)
    if (pos[x] == -1) {
      grid[at] = unval(x);
      pos[x] = at++;
    }
  fgets(line, 1500, stdin);
  assert(strlen(line) <= 1001 && line[strlen(line)-1] == '\n');
  for (char *s = line, *t = line; ; ++s) {
    if (islower(*s) || !*s)
      *t++ = *s;
    if (!*s)
      break;
  }
  for (char *s = line; *s; ++s) {
    int c1 = val(*s++);
    int c2 = val(*s);
    if (!c2 || c1 == c2)
      c2 = val('x'), --s;
    if (pos[c1]/5 == pos[c2]/5)
      printf("%c%c", shiftr(pos[c1]), shiftr(pos[c2]));
    else if (pos[c1]%5 == pos[c2]%5)
      printf("%c%c", shiftd(pos[c1]), shiftd(pos[c2]));
    else
      printf("%c%c", grid[pos[c1]/5*5 + pos[c2]%5], grid[pos[c2]/5*5 + pos[c1]%5]);
  }
  printf("\n");
  return 0;
} 
