#include <limits.h>
 
int divide(int s_a, int s_b) {
  int result;
  if ((s_b == 0) || ((s_a == INT_MIN) && (s_b == -1))) {
    return INT_MAX;
  } 
  else {
    result = s_a / s_b;
  }
  return result;
}
