int vasprintf(char **str, const char *fmt, va_list args) {
  int size = 0;
  va_list tmpa;
  __builtin_va_copy(tmpa, args);
  size = vsnprintf(NULL, size, fmt, tmpa);
  __builtin_va_end(tmpa);
  if (size < 0) { return -1; }
  *str = (char *)malloc(size + 1);
  if (NULL == *str) { return -1; }
  size = vsprintf(*str, fmt, args);
  return size;
}
int asprintf(char **str, const char *fmt, ...) {
  int size = 0;
  va_list args;
  __builtin_va_start(args, fmt);
  size = vasprintf(str, fmt, args);
  __builtin_va_end(args);
  return size;
}
char*concatc(char*a, char b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%c",a,b);
  return ptr;
}
char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}

char*defangIPaddr(char*address){
    char*result = strdup("");
    for(int z=0; address[z];z++){char c = address[z];
        if(c == '.')
            result = concats(result, "[.]");
        else
            result = concatc(result, c);
    }
    return result;
}
