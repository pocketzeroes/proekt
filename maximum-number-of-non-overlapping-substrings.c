#define pbs(zpv, zvv) zpv.ptr = pushbackS(zpv.ptr, &zpv.sz, zvv)
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
char**pushbackS(char**array, int *size, char*value) {
  char**output = resizeArray(array, char*, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
  char**ptr;
  int sz;
}vecs;
vecs newVecS(){
  vecs rez;
  rez.ptr = NULL;
  rez.sz  = 0;
  return rez;
}
char*substr(const char* str, size_t begin, size_t len){
  if(str == 0 || strlen(str) == 0 || strlen(str) < begin || strlen(str) < (begin+len))
    return strdup(""); 
  return strndup(str + begin, len); 
} 
///////////////////////////////////////
void amin(int*x, int y){
    if(y < *x)
      *x = y;
}
void amax(int*x, int y){
    if(*x<y)
       *x=y;
}

int dp[100011][27];
int prv[100011][27];
int first_occur[26];
int last_occur[26];


char**maxNumOfSubstrings(char*s, int*rsz){
    int s_size = strlen(s);
    memset(first_occur, -1, sizeof first_occur);
    memset( last_occur, -1, sizeof  last_occur);
    for(int i=0, i_len=(s_size); i<i_len; ++i) {
        int k = s[i] - 'a';
        if (first_occur[k] == -1)
            first_occur[k] = i;
        last_occur[k] = i;
    }
    memset(dp, 0x3f, sizeof dp);
    memset(prv, 0, sizeof prv);
    dp[0][0] = 0;
    for(int i=0, i_len=(s_size); i<i_len; ++i) for(int j=0, j_len=(27); j<j_len; ++j) if (dp[i][j] <= (int)s_size){
        int k = s[i] - 'a';
        if(first_occur[k] == i) {
            int right = i + 1;
            int left = i;
            for(int p=i; p<right; p++) {
                amax(&right, last_occur[s[p] - 'a'] + 1);
                amin(&left, first_occur[s[p] - 'a']);
            }
            if(i == left && dp[right][j+1] > dp[i][j] + right - i) {
                dp[right][j+1] = dp[i][j] + right - i;
                prv[right][j+1] = i;
            }
        }
        if(dp[i+1][j] > dp[i][j]){
            dp[i+1][j] = dp[i][j];
            prv[i+1][j] = -1;
        }
    }
    for(int c=26; c>=0; c--){
        if(dp[s_size][c] <= (int)s_size){
            int index = s_size;
            vecs ans = newVecS();
            while(c){
                int p = prv[index][c];
                if(p == -1)
                    index--;
                else{
                    pbs(ans, substr(s, p, index-p));
                    index = p;
                    c--;
                }
            }
           *rsz=ans.sz;
            return ans.ptr;
        }
    }
    assert(false);
    return NULL;
}
