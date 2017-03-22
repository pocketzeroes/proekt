void inplace_reverse(char * str)
{
  if (str)
  {
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end)
    {
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}

char*addStrings(char*num1,char*num2){
    char*result=strdup("");
    char*ptr;
    for (int i = strlen(num1) - 1, j = strlen(num2) - 1, carry = 0;
        i >= 0 || j >= 0 || carry;
        carry /= 10) {
        if (i >= 0) 
            carry += num1[i--] - '0';
        if (j >= 0) 
            carry += num2[j--] - '0';
        asprintf(&ptr,"%s%d", result, carry % 10);
        free(result);
        result=ptr;
    }
    inplace_reverse(result);
    return result;
}
