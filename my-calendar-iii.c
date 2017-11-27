typedef struct{
}MyCalendarThree;
MyCalendarThree*gptr;
int max(int a,int b){return a>b?a:b;}

int mx;


typedef struct node{
    int l, r, m, times;
    struct node*left;
    struct node*right;
}node;
node*root;
node*newNode(int a, int b, int t){
    node*rez=malloc(sizeof(node));
    rez->l     = a;
    rez->r     = b;
    rez->m     = 0;
    rez->times = t;
    rez->left  = NULL;
    rez->right = NULL;
    return rez;
}
MyCalendarThree*myCalendarThreeCreate(){
    root = newNode(0, 1000000001, 0);
    mx = 0;
    return gptr;
}
void add(int start, int end, node*ptr){
    if(ptr->m){
        if(end<=ptr->m)
            add(start,end,ptr->left);
        else if(ptr->m<=start)
            add(start,end,ptr->right);
        else{
            add(start,ptr->m,ptr->left);
            add(ptr->m,end,ptr->right);
        }
    }
    else{
        if(start==ptr->l && end==ptr->r)
            mx=max(mx,++ptr->times);
        else if(start==ptr->l){
            ptr->m=end;
            ptr->left=newNode(start,ptr->m,ptr->times+1);
            ptr->right=newNode(ptr->m,ptr->r,ptr->times);
            mx=max(mx,ptr->times+1);
        }
        else if(end==ptr->r){
            ptr->m=start;
            ptr->left=newNode(ptr->l,ptr->m,ptr->times);
            ptr->right=newNode(ptr->m,ptr->r,ptr->times+1);
            mx=max(mx,ptr->times+1);
        }
        else{
            ptr->m=start;
            ptr->left=newNode(ptr->l,ptr->m, ptr->times);
            ptr->right=newNode(ptr->m,ptr->r, ptr->times);
            add(start,end,ptr->right);
        }
    }
}
int myCalendarThreeBook(MyCalendarThree*_oo, int start, int end){
    add(start, end, root);
    return mx;
}
void myCalendarThreeFree(MyCalendarThree*_oo){
    root=NULL;
    mx=0;
}
