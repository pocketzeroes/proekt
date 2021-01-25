#define clr(arr)do{ memset(arr, 0, sizeof(arr)); }while(0)
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}
int ok[505][505];
int ook[505];
int vis[505];

int minimumTeachings(int n, int**languages, int languagesSz, int*languages0sz, int**friendships, int friendshipsSz, int*friendships0sz){
  clr(ok);
  clr(ook);
  clr(vis);
  int ans=500;
  for(int i=0; i<languagesSz; i++){
    for(int z=0;z<languages0sz[i];z++){int it=languages[i][z];
      ok[i][it]=1;
    }
  }
  for(int i = 0;i<friendshipsSz;i++){
    friendships[i][0]--;
    friendships[i][1]--;
    for(int j = 1;j<=n;j++){
      if(ok[friendships[i][0]][j]&&ok[friendships[i][1]][j])
        ook[i]=1;
    }
  }
  for(int i = 1;i<=n;i++){
    fill(vis, languagesSz, 0);
    for(int j = 0;j<friendshipsSz;j++){
      if(!ook[j]){
        if(!ok[friendships[j][0]][i]){
          vis[friendships[j][0]]=1;
        }
        if(!ok[friendships[j][1]][i]){
          vis[friendships[j][1]]=1;
        }
      }
    }
    int sum=0;
    for(int j = 0;j<languagesSz;j++){
      sum+=vis[j];
    }
    ans = fmin(ans, sum);
  }
  return ans;
}
