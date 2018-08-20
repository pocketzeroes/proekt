int comp(const void*a,const void*b){
    return *(int*)b-*(int*)a;
}
typedef struct{
    int th;
    int val;
    struct KthLargest*next;
} KthLargest;

KthLargest*kthLargestCreate(int k, int* nums, int numsSize){
    qsort(nums,numsSize,sizeof(int),comp);
    KthLargest* head=(KthLargest*)malloc(sizeof(KthLargest));
    head->th=k;
    head->next=NULL;
    KthLargest* q=head;
    for(int i=0;i<numsSize;i++){
        KthLargest* p=(KthLargest*)malloc(sizeof(KthLargest));
        p->val=nums[i];
        p->next=NULL;
        q->next=p;
        q=p;
    }
    return head;
}
int kthLargestAdd(KthLargest* obj, int val){
    KthLargest* p=obj;
    KthLargest* q=obj->next;
    while(q){
        if(val<q->val){
            p=q;
            q=q->next;
        }
        else{
            KthLargest* s=(KthLargest*)malloc(sizeof(KthLargest));
            s->val=val;
            p->next=s;
            s->next=q;
            break;
        }
    }
    if(q==NULL){
        KthLargest* s=(KthLargest*)malloc(sizeof(KthLargest));
        s->val=val;
        p->next=s;
        s->next=q;
    }
    p=obj;
    for(int i=0;i<obj->th;i++)
        p=p->next;
    return p->val;
}
void kthLargestFree(KthLargest* obj) {
    free(obj);
}
