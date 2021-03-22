#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
typedef struct {
}AuthenticationManager;
AuthenticationManager*gptr;

int  sz;
char*str[3000];
int  ttm[3000];
int t;

AuthenticationManager*authenticationManagerCreate(int timeToLive){
  clr(str);
  clr(ttm);
  t = timeToLive;
  sz = 0;
  return gptr;
}
void authenticationManagerGenerate(AuthenticationManager* obj, char*tokenId, int currentTime){
  str[sz] = strdup(tokenId);
  ttm[sz++] = currentTime + t;
}
void authenticationManagerRenew(AuthenticationManager* obj, char * tokenId, int currentTime){
  int i;
  for(i=0;i<sz;i++){
    if(strcmp(str[i], tokenId)==0 && ttm[i] > currentTime){
      ttm[i] = currentTime + t;
    }
  }
}
int authenticationManagerCountUnexpiredTokens(AuthenticationManager*obj, int currentTime){
  int i;
  int res = 0;
  for(i=0; i<sz; i++){
    if(ttm[i] > currentTime){
      res++;
    }
  }
  return res;
}
void authenticationManagerFree(AuthenticationManager*obj){
  for(int z=0;z<3000;z++)
    if(str[z])
      free(str[z]);
}
