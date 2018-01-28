enum{ N = 10000};
int tr[N];

void add(int x) {
  for (; x < N; x += x & -x)
    ++tr[x];
}
int get(int x) {
  int s = 0;
  for (; x; x -= x & -x)
    s += tr[x];
  return s;
}
bool isIdealPermutation(int*A, int Asz){
    memset(tr, 0, sizeof(tr));
  int local = 0;
  for (int i = 1; i < Asz; ++i)
    local += A[i - 1] > A[i];
  int global = 0;
  for (int i = Asz - 1; i >= 0; --i) {
    int x = A[i];
    ++x;
    global += get(x);
    add(x);
  }
  return global == local;
}

