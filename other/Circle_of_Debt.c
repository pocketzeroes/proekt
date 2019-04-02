#include <stdio.h>

enum{ MAXM = 20000};
int n,lsum,ssum;
int lgsum[3],smsum[3];
int D[3];
int C[3][6];
const int E[6]={100,50,20,10,5,1};
const int Z[6]={10,5,2,1,5,1};
int V[6];
int Mx[2][2][2001][2001];

int main(){
  int i,j,k,q,l,m,best;
  int R[3];
  int dir[2];
  scanf("%d", &n);
  while(n--){
    int ab,bc,ca;
    scanf("%d %d %d", &ab, &bc, &ca);
    D[0]=ab-ca;
    D[1]=bc-ab;
    D[2]=ca-bc;
    lsum=ssum=0;
    for (i=0;i<3;i++){
      lgsum[i]=smsum[i]=0;
      for (j=0;j<6;j++){
        scanf("%d", &C[i][j]);
        lgsum[i]+=(j<4)*C[i][j]*E[j];
        smsum[i]+=(j>3)*C[i][j]*E[j];
      }
      lsum+=lgsum[i];
      ssum+=smsum[i];
    }
    if (lgsum[0]+smsum[0]<D[0] || lgsum[1]+smsum[1]<D[1] || lgsum[2]+smsum[2]<D[2])
      printf("impossible\n");
    else{
      for (q=0;q<2;q++)
        for (j=0;j<(q?ssum+1:(lsum/10)+1);j++)
          for (k=0;k<(q?ssum+1:(lsum/10)+1)-j;k++)
            Mx[q][0][j][k]=MAXM;
      Mx[0][0][lgsum[0]/10][lgsum[1]/10]=0;
      Mx[1][0][smsum[0]][smsum[1]]=0;
      dir[0]=dir[1]=0;
      D[0]=lgsum[0]+smsum[0]-D[0];
      D[1]=lgsum[1]+smsum[1]-D[1];
      for (i=0;i<6;i++){
        int q=i>3;
        int which=q?9-i:i;
        int who;
        for (j=0;j<(q?ssum+1:(lsum/10)+1);j++)
          for (k=0;k<(q?ssum+1-j:(lsum/10)+1-j);k++)
            Mx[q][1-dir[q]][j][k]=MAXM;
          for (j=0;j<(q?ssum+1:(lsum/10)+1);j++)
            for (k=0;k<(q?ssum+1-j:(lsum/10)+1-j);k++)
              if (Mx[q][dir[q]][j][k]<MAXM)
                for (who=0;who<3;who++){
                  for (l=0;l<(C[who][which])+1;l++){
                    R[0]=j;R[1]=k;
                    if (who==0) {R[0]-=l*Z[which]; R[1]+=l*Z[which]; if (q && ((R[1]-D[1])%E[which-1])!=0) continue;}
                    if (who==1) {R[1]-=l*Z[which]; if (q && ((R[0]-D[0]+R[1]-D[1])%E[which-1])!=0) continue;}
                    if (who==2) {R[0]+=l*Z[which]; if (q && ((R[0]-D[0])%E[which-1])!=0) continue;}
                    for (m=0;m<(C[who][which])+1-l ;m++){
                      if (Mx[q][1-dir[q]][R[0]][R[1]]>m+l+Mx[q][dir[q]][j][k])
                        Mx[q][1-dir[q]][R[0]][R[1]]=m+l+Mx[q][dir[q]][j][k];
                      if (who==0) R[0]-=Z[which];
                      if (who==1) {R[1]-=Z[which];R[0]+=Z[which];}
                      if (who==2) R[1]+=Z[which];
                    }
                  }
                  for (l=0;l<(C[(who+1) %3][which])+1;l++){
                    R[0]=j;R[1]=k;
                    if (who==0) {R[0]+=l*Z[which]; R[1]-=l*Z[which]; if (q && ((R[1]-D[1])%E[which-1])!=0) continue;}
                    if (who==1) {R[1]+=l*Z[which]; if (q && ((R[0]-D[0]+R[1]-D[1])%E[which-1])!=0) continue;}
                    if (who==2) {R[0]-=l*Z[which]; if (q && ((R[0]-D[0])%E[which-1])!=0) continue;}
                    for (m=0;m<(C[(who+2) %3][which])+1;m++){
                      if (Mx[q][1-dir[q]][R[0]][R[1]]>m+l+Mx[q][dir[q]][j][k])
                        Mx[q][1-dir[q]][R[0]][R[1]]=m+l+Mx[q][dir[q]][j][k];
                      R[who]+=Z[which];
                      R[(who+2) %3]-=Z[which];
                    }
                  }
                }
        dir[q]=1-dir[q];
      }
      best=MAXM;
      for (j=D[0]%10;j<ssum+1;j+=10)
        for (k=D[1]%10;k<ssum+1-j;k+=10)
          if (D[0]-j>=0 && D[1]-k>=0 && D[0]+D[1]-j-k<lsum+1)
            if (Mx[0][dir[0]][(D[0]-j)/10][(D[1]-k)/10]+Mx[1][dir[1]][j][k]<best)
              best=Mx[0][dir[0]][(D[0]-j)/10][(D[1]-k)/10]+Mx[1][dir[1]][j][k];
      if (best<MAXM)
        printf("%d\n", best);
      else
        printf("impossible\n");
    }
  }
  return 0;
}
