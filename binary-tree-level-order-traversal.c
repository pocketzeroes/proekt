typedef struct TreeNode TreeNode;
int**levelOrder(TreeNode*root, int**columnSizes, int*returnSize){
    if(returnSize==NULL) return NULL;
    if(root==NULL)       return NULL;
    *returnSize=0;
    int num = 0;
    int pre = 0;
    int cur = 1;
    int *columnSizesArray=malloc(sizeof(int )*1000);
    int **retArray=(int**)malloc(sizeof(int*)*1000);
    TreeNode*tempArray[2][1000];
    tempArray[pre][0]=root;
    num++;
    retArray[*returnSize]=malloc(sizeof(int)*num);
    retArray[*returnSize][0]=root->val;
    columnSizesArray[*returnSize]=num;
    (*returnSize)++;
    int temp=0;
    int i=0;
    while(num>0){
        temp=num;
        num=0;
        for(i=0;i<temp;i++){
            if(tempArray[pre][i]->left){
                tempArray[cur][num]=tempArray[pre][i]->left; num++;
            }
            if(tempArray[pre][i]->right){
                tempArray[cur][num]=tempArray[pre][i]->right;num++;
            }
        }
        if(num>0){
          retArray[*returnSize]=malloc(sizeof(int)*num);
          for(i=0;i<num;i++){
            retArray[*returnSize][i]=tempArray[cur][i]->val;
          }
          columnSizesArray[*returnSize]=num;
          (*returnSize)++;
        }
        pre=!pre;
        cur=!cur;
    }
   *columnSizes=columnSizesArray;
    return retArray;
}

