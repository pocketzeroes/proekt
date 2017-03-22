typedef struct NestedInteger NestedInteger;
int gIndex;
bool isNumber(char c){
    return '0' <= c && c <= '9';
}
NestedInteger*parseNumber(char*s){
    int n = 0;
    int positive = 1;
    if (s[gIndex] == '-') {
        positive = -1;
        gIndex++;
    }
    while( s[gIndex] ){
        char c = s[gIndex];
        if (isNumber(c)) {
            n = 10 * n + c - '0';
            gIndex++;
        }
        else 
            break;
    }
    NestedInteger*rez=NestedIntegerInit();
    NestedIntegerSetInteger(rez, n * positive);
    return rez;
}
NestedInteger*parseList(char*s){
    gIndex++;
    NestedInteger*root=NestedIntegerInit();
    while(s[gIndex]){
        char c = s[gIndex];
        if (c == '[') 
            NestedIntegerAdd(root, parseList(s));
        else if (isNumber(c) || c == '-') 
            NestedIntegerAdd(root, parseNumber(s));
        else if (c == ',') 
            gIndex++;
        else if (c == ']') 
            break;
    }
    gIndex++;
    return root;
}
NestedInteger*deserialize(char*s){
    gIndex = 0;
    char c = s[gIndex];
    if (c == '[')
        return parseList  (s);
    else
        return parseNumber(s);
}


























