#include<stdio.h>
#include<stdlib.h>

char zad[250000];

char*incl (char *op, unsigned *in, unsigned *cl){
  unsigned in1, cl1, in2, cl2;
  switch (*op){
    case 'V':
      *in = 1;
      *cl = 1;
      return op + 2;
    case 'C':
      return incl (op + 2, cl, in);
    case 'U':
      op = incl (op + 2, &in1, &cl1);
      op = incl (op, &in2, &cl2);
     *in = in1 + in2;
     *cl = (cl1 > cl2 ? cl1 : cl2);
      return op;
    default:
      abort ();
  }
}
int main(){
  unsigned in, cl;
  while (1){
    if (!gets (zad))
      return 0;
    if (!*zad)
      return 0;
    incl (zad, &in, &cl);
    printf ("%u\n", in);
  }
  return 0;
}
