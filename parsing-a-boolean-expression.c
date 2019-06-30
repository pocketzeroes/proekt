char* substr(const char* str, size_t begin, size_t len){
  if (str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len)) 
    return strdup(""); 
  return strndup(str + begin, len); 
}

bool parseBoolExpr(char*expression) {
    int n = strlen(expression);
    char front = expression[0];
    if (front == 't' || front == 'f') {
        assert(n == 1);
        return front == 't';
    }
    if (front == '!')
        return !parseBoolExpr(substr(expression, 2, n - 3));
    assert(front == '&' || front == '|');
    bool result = front == '&';
    int start = 2, level = 0;
    for (int i = start; i < n; i++) {
        if (level == 0 && (expression[i] == ',' || expression[i] == ')')) {
            bool current = parseBoolExpr(substr(expression, start, i - start));
            if (front == '&')
                result = result && current;
            else
                result = result || current;
            start = i + 1;
            continue;
        }
        if (expression[i] == '(')
            level++;
        else if (expression[i] == ')')
            level--;
    }
    return result;
}
