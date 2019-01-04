typedef long long ll;
typedef struct TreeNode TreeNode;
ll min(ll a, ll b){return a<b?a:b;}

typedef struct{
  ll need;
  ll exi;
  ll no;
}st;
st newst(){
    st rez;
    rez.no  =0;
    rez.need=0;
    rez.exi = INT_MAX;
    return rez;
}
st dfs(TreeNode*root){
    if(root==NULL)
        return newst();
    if(root->left==NULL&&root->right==NULL){
        st a;
        a.need=0;
        a.exi =1;
        a.no  =1;
        return a;
    }
    if(root->left==NULL||root->right==NULL){
        st z;
        if(root->left)
            z=dfs(root->left);
        else
            z=dfs(root->right);
        st a;
        a.exi =z.need+1;
        a.no  =z.exi;
        a.need=z.no;
        return a;
    }
    st l=dfs(root->left);
    st r=dfs(root->right);
    st a;
    a.need = l.no+r.no;
    a.exi  = l.need+r.need+1;
    a.no   = l.exi+r.no;
    a.no   = min(a.no,l.no+r.exi);
    a.no   = min(a.no,a.exi);
    a.need = min(a.need,a.no);
    return a;
}
int minCameraCover(TreeNode* root) {
    st a=dfs(root);
    return a.no;
}
