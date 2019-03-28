#include <stdio.h>

const int perm[6][3]={{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};
char      smap[9]={0,0,0,0,0,0,0,0,0};
int       path[9]={0,1,2,3,4,5,6,7,8};
char      old [9][10],cur[9][10];
int       ix  [9],rowmp[9];

int verify(int cnt, char*map){
  int i,j,found=0;
  char nmap[9];
  if (!cnt)
    return 1;
  else{
    for(i=0;i<cnt && !found;i++)
      if (!(cnt%3) || ((rowmp[cnt]/3) == (path[i]/3))){
        int brk=0;
        for (j=0;j<9;j++)
          nmap[j] = map[j];
        for (j=0; j<9 && !brk; j++){
          char tec=cur[path[i]][ix[j]];
          if (tec!='0'){
            if (map[tec-'1'])
              brk=old[cnt-1][j]!=map[tec-'1'];
            else
              nmap[tec-'1']=old[cnt-1][j];
          }
        }
        if(!brk){
          int tmp=path[i];
          rowmp[cnt-1]=path[i];
          path[i]=path[cnt-1];
          found=verify(cnt-1,(char*)nmap);
          path[i]=tmp;
        }
    }
    return found;
  }
}
int main(){
  int i,j,k,l,m,r,T;
  scanf("%d",&T);
  while(T--){
    int found=0;
    for (i=0;i<9;i++)
      scanf("%s",old[i]);
    for (i=0;i<9;i++)
      scanf("%s",cur[i]);
    for (r=0;r<2 && !found;r++){
      for (i=0;i<6 && !found;i++)
        for (j=0;j<6 && !found;j++)
          for (k=0;k<6 && !found;k++)
            for (l=0;l<6 && !found;l++){
              for (m=0;m<3;m++)
                ix[m]=perm[i][0]*3+perm[j][m];
              for (m=0;m<3;m++)
                ix[3+m]=perm[i][1]*3+perm[k][m];
              for (m=0;m<3;m++)
                ix[6+m]=perm[i][2]*3+perm[l][m];
              found=verify(9,(char*)smap);
            }
      for (i=0;i<9;i++)
        for (j=i;j<9;j++){
          char tmp=old[i][j];
          old[i][j]=old[j][i];
          old[j][i]=tmp;
        }
    }
    if (found)
      printf("Yes\n");
    else
      printf("No\n");
  }
  return 0;
}
