#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}


typedef long long ll;
enum{ N=1003};
char S[N];
int il[N][10];
bool DV[N];
char MN[N],T[N];
char qwe[N];
void pre();
bool check(int v,int n);
bool cmp(int n);

int main(){
    int n;
    scanf("%s",(S+1));
    n=strlen(S+1);
    if(n==1){
        if(S[1]=='8'){
            printf("8\n");
            return 0;
        }
        else{
            printf("-1\n");
            return 0;
        }
    }
    pre();
    for(int i=1;i<=n;i++){
        il[0][(int)S[i]-'0']++;
    }
    bool c=false;
    for(int i=1;i<=1000;i++){
        if(DV[i]){
            if(check(i,n))
                c=true;
        }
    }
    if(!c){
        printf("-1\n");
        return 0;
    }
    for(int i=n;i>=1;i--)
      printf("%c",(char)((int)MN[i]+'0'));
    printf("\n");
    return 0;
}
void pre(){
    for(int i=0;i<=1000;i++){
        MN[i]=9;
        DV[i]=false;
        for(int j=0;j<=9;j++)
          il[i][j]=0;
    }
    for(int i=1;i<=1000;i++){
        if(i%8==0)
            DV[i]=true;
        int tmp=i;
        il[i][tmp%10]++;
        tmp/=10;
        if(i>=10)
            il[i][tmp%10]++;
        tmp/=10;
        if(i>=100)
            il[i][tmp%10]++;
    }
}
bool check(int v,int n){
    if(n>=4){
        if((v<100)&&il[v][0]+1>il[0][0])
            return false;
        if((v<10)&&il[v][0]+2>il[0][0])
            return false;
    }
    for(int i=0;i<=9;i++){
        if(il[v][i]>il[0][i]){
            return false;
        }
    }
    if(n==2) 
        if(v<10||v>99) 
            return false;
    if(n==3) 
        if(v<100||v>999) 
            return false;
    int mn=10;
    if(n>=4){
        for(int i=1;i<=9;i++) 
            if(il[0][i]-il[v][i]!=0) 
                mn=min(mn,i);
        if(mn==10) 
            return false;
    }
    int tmp=v;
    for(int i=1;i<=3;i++){
        T[i]=tmp%10;
        tmp/=10;
    }
    int k=4;
    il[0][mn]-=1;
    for(int i=9;i>=0;i--){
        for(int j=1;j<=il[0][i]-il[v][i];j++)
            T[k]=i, k++;
    }
    il[0][mn]+=1;
    if(n>3) 
        T[n]=mn;
    if(cmp(n)){
        memcpy(&qwe, &T  , sizeof(T));
        memcpy(&T  , &MN , sizeof(T));
        memcpy(&MN , &qwe, sizeof(T));
    }
    return true;
}
bool cmp(int n){
    for(int i=n;i>=1;i--){
        if(MN[i]<T[i]) 
            return false;
        if(MN[i]>T[i]) 
            return true;
    }
    return false;
}








































