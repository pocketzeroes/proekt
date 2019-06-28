#include<stdio.h>
#include<string.h>
#include<assert.h>

char same[256][256], 
     def [256][256], 
     done[256];
char op  [100], lhs, rhs;
int  i,j,k,m,n,c;

int issame(int a, int b){
  int i,r;
  if (same[a][b] == 1) return 1;
  if (same[a][b] == -1) return 0;
  if (isupper(def[a][0])) return issame(def[a][0],b);
  if (isupper(def[b][0])) return issame(a,def[b][0]);
  if (def[a][0] != def[b][0]) return 0;
  if (def[a][0] != 's') return 1;
  same[a][b] = same[b][a] = 1;
  for (i=1;(def[a][i] && def[b][i]) && issame(def[a][i],def[b][i]);i++);
  r = !def[a][i] && !def[b][i];
  same[a][b] = same[b][a] = r-1;
  return r;
}
int main(){
  for (c=0;strcmp(op,"--");c++) {
     if (c) {
        printf("\n"); 
        memset(same,0,sizeof(same)); 
        memset(def,0,sizeof(def));
        memset(done,0,sizeof(done));
     }
     def['i'][0] = 'i'; def['c'][0] = 'c'; def['r'][0] = 'r';
     for (n=0;(1 == scanf("%s",op)) && *op != '-';n++) {
        assert(!strcmp(op,"type"));
        scanf(" %c = %c%*[a-z(]",&lhs,&rhs);
        def[lhs][0] = rhs;
        if (rhs == 's') {
           for (j=1;scanf(" %c",&def[lhs][j]) && def[lhs][j] != ')';j++);
           def[lhs][j] = 0;
        }
     }
     for (i='A';i<='Z';i++) {
        if (!def[i][0] || done[i]) continue;
        printf("%c",i);
        for (j=i+1;j<='Z';j++) {
           if (done[j]) continue;
           if (issame(i,j)) {
              assert(issame(j,i));
              printf(" %c",j);
              done[j] = 1;
           } else assert(!issame(j,i));
        }
        printf("\n");
     }
  }
  return 0;
}
