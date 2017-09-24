int stack[20000];

int calPoints(char**ops, int opsSz){
  memset(stack, 0, sizeof(stack));
  int i, j, n;
  n = opsSz;
  int p = 0;
  for (i=0;i<n;i++){
    if (ops[i][0]=='+'){
      if(p-2 < 0)
        continue;
      stack[p] = stack[p-1] + stack[p-2];
      p++;
    }
    else if (ops[i][0]=='D'){
      if(p-1 < 0)
        continue;
      stack[p] = stack[p-1] * 2;
      p++;
    }
    else if (ops[i][0]=='C'){
      if(p > 0)
        p--;
    }
    else{
      int val = atoi(ops[i]);
      stack[p++] = val;
    }
  }
  int ret = 0;
  for(int i = 0;i < p;i++){
    ret += stack[i];
  }
  return ret;
}
