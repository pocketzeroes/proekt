typedef struct ListNode ListNode;

ListNode*removeZeroSumSublists(ListNode*head){
    int a[2000];
    int p = 0;
    for(;head != NULL; head = head->next){
        a[p++] = head->val;
    }
    int n = p;
    int cum[n+1]; memset(cum, 0, sizeof(cum));
    for(int i = 0;i < n;i++){
        cum[i+1] = cum[i] + a[i];
    }
    bool ng[n]; memset(ng,0,sizeof(ng));
    for(int i = 0;i <= n;i++){
        for(int j = 0;j < i;j++){
            if(cum[j] == cum[i] && !ng[j]){
                for(int k = j;k < i;k++)
                    ng[k] = true;
                break;
            }
        }
    }
    ListNode*root = NULL;
    for(int i = n-1; i >= 0; i--){
        if(!ng[i]){
            ListNode*x =calloc(1,sizeof(ListNode));
            x->val=a[i];
            x->next=root;
            root = x;
        }
    }
    return root;
}
