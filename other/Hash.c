#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

enum{ maxMod = (1 << 25)};

int N, K, Mod, table[maxMod];
long long solution = 0, inv33;

void rec1(int state, int iter){
  if (iter) {
    for (int z = 1; z <= 26; ++z) {
      rec1(((state * 33) ^ z) & Mod, iter - 1);
    }
  }
  else {
    ++table[state];
  }
}
void rec2(int state, int iter) {
  if (iter) {
    for (int z = 1; z <= 26; ++z) {
      rec2(((state ^ z) * inv33) & Mod, iter - 1);
    }
  }
  else {
    solution += table[state];
  }
}
void load() {
  scanf("%d%d%d", &N, &K, &Mod);
  Mod = (1 << Mod);
  int e = Mod / 2 - 1;
  long long b = 33;
  for (inv33 = 1; e; e /= 2) {
    if (e & 1)
      inv33 = (inv33 * b) % Mod;
    b = (b * b) % Mod;
  }
  assert((33ll * inv33) % Mod == 1);
  --Mod;
}
int main(){
  load();
  rec1(0, N / 2);
  rec2(K, N - N / 2);
  printf("%lld\n", solution);
  return 0;
}
