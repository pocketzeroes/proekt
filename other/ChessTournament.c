#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>

#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
  int *output = resizeArray(array, int, *size + 1);
  output[(*size)++] = value;
  return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

enum{ maxn=(int)5e4+10};
vec equ  [maxn];
vec gre  [maxn];
vec Gra  [maxn];
int vis  [maxn];
int Newlv[maxn];
int n,m;
int ok=1;

void Getlv(int u,int lv){
  if(vis[u])
    return;
  Newlv[u]=lv;
  vis[u]=1;
  int sz=equ[u].sz;
  for(int i=0;i<sz;i++){
    int v=equ[u].ptr[i];
    Getlv(v,lv);
  }
}
bool Top_sort(int u){
  vis[u]=-1;
  for(int i=0;i<Gra[u].sz;i++){
    int v=Gra[u].ptr[i];
    if(vis[v]==-1)
      return false;
    else if(!vis[v]&&!Top_sort(v))
      return false;
  }
  vis[u]=1;
  return true;
}
int main(){
  int x,y;
  char ch;
  scanf("%d %d", &n, &m);
  for(int i=0;i<m;i++){
    scanf("%d %c %d", &x, &ch, &y);
    if(ch=='='){
      equ[x].ptr = pushback(equ[x].ptr, &equ[x].sz, y);
      equ[y].ptr = pushback(equ[y].ptr, &equ[y].sz, x);
    }
    else
      gre[x].ptr = pushback(gre[x].ptr, &gre[x].sz, y);
  }
  int lv=0;
  for(int i=0;i<n;i++){
    if(!vis[i]){
      Getlv(i,lv);++lv;
    }
  }
  for(int i=0;i<n;i++){
    int sz=gre[i].sz;
    for(int j=0;j<sz;j++){
      int k=gre[i].ptr[j];
      int u=Newlv[i],
          v=Newlv[k];
      Gra[u].ptr = pushback(Gra[u].ptr, &Gra[u].sz, v);
    }
  }
  memset(vis,0,sizeof vis);
  for(int i=0;i<lv;i++){
    if(!vis[i]){
      if(!Top_sort(i)){
        ok=0;
        break;
      }
    }
  }
  if(ok)
    puts("consistent");
  else
    puts("inconsistent");
  return 0;
}
