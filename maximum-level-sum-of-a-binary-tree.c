typedef struct TreeNode TreeNode;
typedef long long ll;
enum{ MAX =(int) 1e5};
ll sum[MAX];
int mdep;

void dfs(TreeNode* v,int d){
  if(!v) return;
  mdep = fmax(mdep,d);
  sum[d]+=v->val;
  dfs(v->left,d+1);
  dfs(v->right,d+1);
}
int maxLevelSum(TreeNode* root){
  memset(sum,0,sizeof(sum));
  dfs(root,0);
  int ans=0;
  for(int i=0;i<=mdep;i++)
    if(sum[ans]<sum[i]) 
      ans=i;
  return ans+1;
}
