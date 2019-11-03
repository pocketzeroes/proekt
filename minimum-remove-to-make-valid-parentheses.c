void reverse(char * str){
  if (str){
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
char  ans[100000]; int asz;
char rans[100000]; int rsz;

char*minRemoveToMakeValid(char*s){
    asz = rsz = 0;
    int cnt = 0;
    for(int i=0; s[i]; ++i){
        if(s[i] == '('){
            cnt++;
            ans[asz++] = s[i];
        }
        else if(s[i] == ')'){
            if(cnt)
                cnt--, ans[asz++] = s[i];
        }
        else
            ans[asz++] = s[i];
    }
    for(int i = asz-1; i>=0; --i){
        if(cnt && ans[i] == '(')
            --cnt;
        else
            rans[rsz++] = ans[i];
    }
    rans[rsz] = '\0';
    reverse(rans);
    return rans;
}
