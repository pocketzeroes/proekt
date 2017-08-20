typedef long long ll;
typedef struct TreeNode TreeNode;
ll d[100000][2];

void doit(TreeNode* p,int dep,ll x,int b){
  if (p==NULL) return;
  if (b==1) x=0;
  if (x<d[dep][0]) d[dep][0]=x;
  if (x>d[dep][1]) d[dep][1]=x;
  if ((p->left!=NULL)&&(p->right!=NULL)) b=0;
  doit(p->left,dep+1,x+x,b);
  doit(p->right,dep+1,x+x+1,b);
}
 
int widthOfBinaryTree(TreeNode*root){
  int i,j;
  ll ans;
  for (i=0;i<100000;i++){
    d[i][0]=(1LL<<60);
    d[i][1]=-(1LL<<60);
  }
  doit(root,0,0,1);
  ans=0;
  for (i=0;i<100000;i++)
    if (d[i][1]>=d[i][0])
      if (d[i][1]-d[i][0]+1>ans)
        ans=d[i][1]-d[i][0]+1;
  return (int)ans;
}
