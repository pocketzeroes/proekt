char*concats(char*a, char*b){
  char*ptr=NULL;
  asprintf(&ptr, "%s%s", a, b);
  return ptr;
}
void reverse(char * str){
  if (str){
    char * end = str + strlen(str) - 1;
#   define XOR_SWAP(a,b) do\
    {\
      a ^= b;\
      b ^= a;\
      a ^= b;\
    } while (0)
    while (str < end){
      XOR_SWAP(*str, *end);
      str++;
      end--;
    }
#   undef XOR_SWAP
  }
}
///////
char*a;
int n,ne[2005];

char*work(int l, int r){
    char*ans=strdup("");
    if(l>r)
        return ans;
    if(a[l]=='('){
        ans = work(l+1, ne[l]-1);
        reverse(ans);
        return concats(ans, work(ne[l]+1, r));
    }
    if(ans)free(ans);
    ans=strdup(" ");
    ans[0] = a[l];
    return concats(ans, work(l+1, r));
}
char*reverseParentheses(char*s){
    a = s;
    int st[2005],t=0,i;
    n = strlen(a);
    for(i=0;i<n;i++)
        if(s[i]=='(')
            st[++t]=i;
    else if(s[i]==')')
        ne[st[t--]]=i;
    return work(0, n-1);
}
