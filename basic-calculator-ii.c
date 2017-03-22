int compute(int lhs, int rhs, char op) {
  if (op == '+') {
    return lhs + rhs;
  }
  if (op == '-') {
    return lhs - rhs;
  }
  if (op == '*') {
    return lhs * rhs;
  }
  if (op == '/') {
    return lhs / rhs;
  }
  return 0;
}

int calculate(char* s) {
  int n = 0;   
  char ops[2]; 
  int args[2]; 
  int p = 0;   
  ops[0] = '+';
  args[0] = 0;
  char c;
  int i = 0;
  while(c = s[i++], c != 0) {
    if (c == ' ') {
      continue;
    }
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      if (ops[p] == '*' || ops[p] == '/') {
        n = compute(args[p], n, ops[p]);
        --p;
      }
      if (c == '+' || c == '-') {
        args[p] = compute(args[p], n, ops[p]);
        ops[p] = c;
      } else {
        args[p + 1] = n;
        ops[p + 1] = c;
        ++p;
      }
      n = 0;
    } else {
      n = n * 10 + c - '0';
    }
  }
  if (ops[p] == '*' || ops[p] == '/') {
    n = compute(args[p], n, ops[p]);
  }
  return compute(args[0], n, ops[0]);
}

