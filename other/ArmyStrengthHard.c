#include <stdio.h>
#include <stdlib.h>

const char* war(int* godzilla, int ng, int* mechagodzilla, int nm) {
  int i = 0; 
  int j = 0; 
  while (i < ng && j < nm) {
    if (mechagodzilla[j] <= godzilla[i])
      j += 1;
    else
      i += 1;
  }
  return (i >= ng)?"MechaGodzilla":"Godzilla";
}

int main() {
  int n;
  int ng, nm;
  int* godzilla = NULL;
  int* mechagodzilla = NULL;
  scanf("%d", &n);
  while (n--) {
    scanf("%d %d", &ng, &nm);
    godzilla = (int*) realloc(godzilla, ng*sizeof(int));
    mechagodzilla = (int*) realloc(mechagodzilla, nm*sizeof(int));
    for (int i = 0; i<ng; ++i) {
      scanf("%d", godzilla+i);
    }
    for (int i = 0; i<nm; ++i) {
      scanf("%d", mechagodzilla+i);
    }
    printf("%s\n", war(godzilla, ng, mechagodzilla, nm));
  }
  return 0;
}
