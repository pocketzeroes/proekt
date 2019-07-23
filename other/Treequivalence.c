#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char a[1000], b[1000];
int t,i,j;

struct nn {
  int n; char lbl;
  struct nn *fwd[100];
  int fwdi[100];
} n[200], *p, *root1, *root2;

char * parse(int depth,char *x, int ni, struct nn **r) {
  char lbl = *x++;
  struct nn *pp = p++;
  int i;
  pp->n=ni;
  pp->lbl = lbl;
  if (*x == '(') {
     while (*x == ',' || *x == '(') {
        x = parse(depth+1,++x,1,&pp->fwd[pp->n]);
        pp->fwdi[pp->n] = 0;
        pp->fwd[pp->n]->fwd[0] = pp;
        pp->fwd[pp->n]->fwdi[0] = pp->n;
        pp->n++;
     }
     x++;
  }
  *r = pp;
  return x;
}
int comp(struct nn *t, struct nn *u, int w, int x){
   int i,j;
   if (t->n != u->n | t->lbl != u->lbl) return 0;
   if (w == -1) return comp(t->fwd[0],u->fwd[0],t->fwdi[0],u->fwdi[0]);
   j = (x+1)%u->n;
   for (i=(w+1)%t->n;i!=w;i=(i+1)%t->n) {
      if (!comp(t->fwd[i],u->fwd[j],t->fwdi[i],u->fwdi[j])) return 0;
      j = (j+1)%u->n;
   }
   return 1;
}
int equiv(struct nn *t, int where,int depth){
   int i;
   if (t->n == 1 && comp(t,root1,-1,-1)) return 1;
   if (where == -1) {
      for (i=0;i<t->n;i++) {
         if(equiv(t->fwd[i],t->fwdi[i],depth+1)) return 1;
     }
   }else{
      for (i=(where+1)%t->n;i!=where;i=(i+1)%t->n) if(equiv(t->fwd[i],t->fwdi[i],depth+1)) return 1;
   }
   return 0;
}
int main(){
  scanf("%d ",&t);
  while (t--) {
     p = n;
     if (!gets(a)) {printf("short input\n"); exit(1); }
     parse(0,a,0,&root1);
     while(root1->n > 1)root1=root1->fwd[1];
     if (!gets(b)) {printf("short input\n"); exit(1); }
     parse(0,b,0,&root2);
     if(!strcmp(a,b) || equiv(root2,-1,0)) printf("same\n");else printf("different\n");
  }
  if (gets(a)) printf("extraneous input!\n");
  return 0;
}
