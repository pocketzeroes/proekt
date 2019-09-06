#include<stdio.h>
#include<string.h>
#include<stdlib.h>

static char buf[200005];
static char out[200005];
static int state[200005];
static int aut[1000][26];
static int final;

static void automat (const char *ret){
  int i, back;
  char ac, c;
  memset (aut, 0, sizeof (aut));
  final = strlen (ret);
  if (final > sizeof (aut) / (26 * sizeof (int))){
    fprintf (stderr, "prilis dlouhy BUG\n");
    abort ();
  }
  aut[0][ret[0] - 'A'] = 1;
  back = 0;
  for (i = 1; i < final; i++){
    ac = ret[i];
    aut[i][ac - 'A'] = i + 1;
    for (c = 'A'; c <= 'Z'; c++){
      if (c == ac)
        continue;
      aut[i][c - 'A'] = aut[back][c - 'A'];
    }
    back = aut[back][ac - 'A'];
  }
}
static void add_char (char c, int *end){
  int ast = state[*end];
  if (c < 'A' || c > 'Z'){
    out[*end] = c;
    (*end)++;
    state[*end] = 0;
    return;
  }
  ast = aut[ast][c - 'A'];
  if (ast == final){
    (*end) -= (final - 1);
    return;
  }
  out[*end] = c;
  (*end)++;
  state[*end] = ast;
}
int main(){
  int i, n;
  char hled[2000], *p;
  int outend = 0;
  while (gets (buf) && sscanf (buf, "%d%s", &n, hled) == 2){
    automat (hled);
    for (i = 0; i < n; i++){
      gets (buf);
      outend = 0;
      state[0] = 0;
      for (p = buf; *p; p++)
        add_char (*p, &outend);
      out[outend] = 0;
      puts (out);
    }
  }
  return 0;
}
