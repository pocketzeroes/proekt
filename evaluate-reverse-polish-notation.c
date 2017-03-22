int evalRPN(char** tokens, int tokensSize) {
    int i = 1;
    int* buffer;
    buffer = (int*)malloc(sizeof(int) * tokensSize);
    int* top = buffer;
    *top = atoi(tokens[0]);
    for (; i < tokensSize; ++i) {
        switch(tokens[i][0]) {
          case '+':
            *(top - 1) += *top;
            top -= 1;
            break;
          case '-':
            if (atoi(tokens[i]) != 0) {
                top += 1;
                *top = atoi(tokens[i]);
                break;
            }
            *(top - 1) -= *top;
            top -= 1;
            break;
          case '*':
            *(top - 1) *= *top;
            top -= 1;
            break;
          case '/':
            *(top - 1) /= *top;
            top -= 1;
            break;
          default:
            top += 1;
            *top = atoi(tokens[i]);
        }
    }
    int res = *top;
    free(buffer);
    return res;
}
