void helper(char* s, char*** res, int** columnSizes, int* returnSize, char** stack, int top) {
    int i;
    if (*s == '\0') {
        res[(* returnSize)] = malloc(sizeof(char*) * top);
        (* columnSizes)[(* returnSize)] = top;
        for (i = 0 ; i < top ; i++) {
            res[(* returnSize)][i] = stack[i];
        }
        (* returnSize)++;
        return;
    }
    char* c = s;
    while (*c != '\0') {
        bool isPalin = true;
        for (i = c-s ; i >= 0 ; i--) {
            if (*(c+i) != *(c-i)) { 
                isPalin = false;
                break;
            }
        }
        if (isPalin) {
            int length = (c-s)*2+1;
            char* tmp = malloc(length+1);
            memcpy(tmp, s, length);
            tmp[length] = '\0';
            stack[top++] = tmp;
            helper(s+length, res, columnSizes, returnSize, stack, top);
            top--;
        }
        isPalin = true;
        for (i = c-s ; i >= 0 ; i--) {
            if (*(c+1+i) != *(c-i)) {
                isPalin = false;
                break;
            }
        }
        if (isPalin) {
            int length = (c-s)*2+2;
            char* tmp = malloc(length+1);
            memcpy(tmp, s, length);
            tmp[length] = '\0';
            stack[top++] = tmp;
            helper(s+length, res, columnSizes, returnSize, stack, top);
            top--;
        }
        c++;
    }
}
char*** partition(char* s, int** columnSizes, int* returnSize) {
    char*** res = malloc(sizeof(char**) * 1000);
    (* columnSizes) = malloc(sizeof(int) * 1000);
    (* returnSize) = 0;
    char* stack[strlen(s)];
    int top = 0;
    helper(s, res, columnSizes, returnSize, stack, top);
    return res;
}



