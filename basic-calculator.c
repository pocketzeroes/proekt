#define STACK_SIZE 1024
static long parens[STACK_SIZE];
static long parens_head = 0;
int calculate(char* s)
{
  int acc = 0;
  int sign = 0;
  while (*s != '\0') {
    if (*s == ' ' || *s == '\t') {
      ++s;
      continue;
    } if (*s == '(') {
      ++parens_head;
      if (sign == 0) {
      	parens[parens_head] = parens[parens_head-1];
      } else {
	    parens[parens_head] = ~parens[parens_head-1];
      }
      sign = 0; 
      ++s;
    } else if (*s == '+') {
      sign = 0;
      ++s;      
    } else if (*s == '-') {
      sign = -1;
      ++s;      
    } else if (*s == ')') {
      --parens_head;
      ++s;      
    } else {
      char* p;
      int x = 0;
      while(*s >= '0' && *s <= '9') {
    	x = 10*x + *s++ - '0';
      }
      if (sign != parens[parens_head]) {
	    acc -= x;
      } else {
	    acc += x;
      }
    }
  }
  return acc;
}
