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
typedef struct{
    bool b[26];
}vector;
bool isempty(vector*vb){
    for(int i=0;i<26;i++)
        if(vb->b[i])
            return false;
    return true;
}
char*smallestSubsequence(char*s){
    int ssize=strlen(s);
    int last=-1;
    vector have = {};
    for(int i=0; i<ssize; i++)
        have.b[s[i]-'a']=1;
    char*ans = strdup("");
    while(true){
        if(isempty(&have))
            break;
        for(int i=0; i<26; i++)
            if(have.b[i]){
                vector aux = have;
                int second=last+1;
                for(int j=second; j<ssize; j++){
                    if(s[j]==('a'+i)){
                        second=j;
                        break;
                    }
                }
                aux.b[i]=0;
                for(int j=second+1; j<ssize; j++){
                    if(aux.b[s[j]-'a'])
                       aux.b[s[j]-'a']=0;
                }
                if(isempty(&aux)){
                    ans = concatc(ans, ('a'+i));
                    last = second;
                    have.b[i]=0;
                    break;
                }
            }
        if(isempty(&have))
            break;
    }
    return ans;
}
