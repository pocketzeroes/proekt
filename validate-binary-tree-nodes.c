int c[10001];

bool validateBinaryTreeNodes(int n, int*leftChild, int leftChildSz, int*rightChild, int rightChildSz){
    for(int i=0;i<n;i++)
        c[i]=0;
    for(int i=0;i<n;i++)
        if(leftChild[i]!=-1)
            c[leftChild[i]]++;
    for(int i=0;i<n;i++)
        if(rightChild[i]!=-1)
            c[rightChild[i]]++;
    int cnt=0;
    for(int i=0;i<n;i++){
        if(c[i]>1)
            return false;
        if(c[i]==0)
            cnt++;
    }
    return cnt==1;
}
