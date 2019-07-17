#pragma GCC optimize "-O3"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
typedef long long ll;
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}
int in_nextInt(){
  int x;
  scanf("%d", &x);
  return x;
}
void fill(int*arr, int sz, int val){
  for(int i=0; i<sz; i++)
    arr[i] = val;
}

int  n, k, m;
int  primes   [  10000];
int  np;
int  sequence [ 100000];
int  factors[100001][7];
int  last     [  10000];
int  intervals[1000000];
int  sums     [1000000];
bool ina      [  10000];
bool inb      [  10000];


typedef struct Node{
    int         value;
    int         height;
    struct Node*left;
    struct Node*right;
    struct Node*parent;
    struct Node*prev;
    struct Node*next;
}Node;
Node*root;
Node*trees[10000];

void balance(Node*n);

Node*newNode(int v){
    Node*rez = calloc(1, sizeof(Node));
    rez->value = v;
    return rez;
}
int leftheight(Node*n){
    return n->left==NULL?0:n->left->height;
}
int rightheight(Node*n){
    return n->right==NULL ? 0 : n->right->height;
}
void recalc(Node*n){
    n->height = 1 + max(leftheight(n), rightheight(n));
}
void rotateleft(Node*n){
    Node*p = n->parent;
    Node*pivot = n->right;
    Node*subtree = pivot->left;
    n->right = subtree;
    if(subtree!=NULL)
        subtree->parent = n;
    n->parent = pivot;
    pivot->left = n;
    if(p==NULL)
        root = pivot;
    else if(p->left == n)
        p->left = pivot;
    else
        p->right = pivot;
    pivot->parent = p;
    recalc(n);
    recalc(pivot);
    if(p!=NULL)
        recalc(p);
}
void rotateright(Node*n){
    Node*p     = n->parent;
    Node*pivot = n->left;
    Node*subtree = pivot->right;
    n->left = subtree;
    if(subtree!=NULL)
        subtree->parent = n;
    n->parent = pivot;
    pivot->right = n;
    if(p==NULL)
        root = pivot;
    else if(p->left == n)
        p->left = pivot;
    else
        p->right = pivot;
    pivot->parent = p;
    recalc(n);
    recalc(pivot);
    if(p!=NULL)
        recalc(p);
}
void insert(Node*n, Node*node){
    if(node->value <= n->value){
        if(n->left==NULL){
            n->left = node;
            node->parent = n;
            Node*prevnode = n->prev;
            node->next = n;
            node->prev = prevnode;
            n->prev = node;
            if(prevnode!=NULL)
                prevnode->next = node;
        }
        else
            insert(n->left, node);
    }
    else{
        if(n->right==NULL){
            n->right = node;
            node->parent = n;
            Node*nextnode = n->next;
            node->prev = n;
            node->next = nextnode;
            n->next = node;
            if(nextnode!=NULL)
                nextnode->prev = node;
        }
        else
            insert(n->right, node);
    }
    balance(n);
}
Node*find(Node*n, int target){
    Node*result = n;
    if(target < n->value){
        if(n->left!=NULL)
            result = find(n->left, target);
    }
    else if(target > n->value){
        if(n->right!=NULL)
            result = find(n->right, target);
    }
    return result;
}
void delete(Node*n, int target){
    if(target == n->value){
        if(n->next!=NULL)
            n->next->prev = n->prev;
        if(n->prev!=NULL)
            n->prev->next = n->next;
        Node*replacement = NULL;
        if(n->left==NULL)
            replacement = n->right;
        else if(n->right==NULL)
            replacement = n->left;
        else{
            recalc(n);
            replacement = leftheight(n) >= rightheight(n) ? n->prev : n->next;
            if(replacement == n->left){
                replacement->right = n->right;
                n->right->parent = replacement;
            }
            else if( replacement == n->right){
                replacement->left = n->left;
                n->left->parent = replacement;
            }
            else if(replacement!=NULL){
                Node*kid = replacement->left==NULL ? replacement->right : replacement->left;
                if(replacement->parent->left==replacement)
                    replacement->parent->left = kid;
                else
                    replacement->parent->right = kid;
                if(kid!=NULL)
                    kid->parent = replacement->parent;
                for(Node*node = replacement->parent; node!=n && node!=NULL; node = node->parent)
                    balance(node);
                replacement->left  = n->left;
                replacement->right = n->right;
                n->left->parent = replacement;
                n->right->parent = replacement;
            }
        }
        if(replacement!=NULL && replacement->parent == n->parent)
            assert(!"PANIC!");
        if(n->parent==NULL)
            root = replacement;
        else if(n->parent->left==n)
            n->parent->left = replacement;
        else
            n->parent->right = replacement;
        if(replacement!=NULL)
           replacement->parent = n->parent;
        n->parent = n->left = n->right = n->next = n->prev = NULL;
    }
    else if(target < n->value)
        delete(n->left, target);
    else
        delete(n->right, target);
    balance(n);
}
void balance(Node*n){
    recalc(n);
    if(leftheight(n)-rightheight(n)>1){
        if(rightheight(n->left) > leftheight(n->left))
            rotateleft(n->left);
        rotateright(n);
    }
    else if(rightheight(n) - leftheight(n)>1){
        if(leftheight(n->right) > rightheight(n->right))
            rotateright(n->right);
        rotateleft(n);
    }
}




void adjust( int lo, int hi, int min, int max, int index, int delta ){
    int left = index+index;
    int right = left+1;
    if( lo<=min && max<=hi )
        intervals[index] += delta;
    else{
        int mid = (min+max)/2;
        if( min<=hi && lo<=mid )
            adjust( lo, hi, min, mid, left, delta );
        if( mid+1<=hi && lo<=max )
            adjust( lo, hi, mid+1, max, right, delta );
    }
    sums[index] = (intervals[index]>0) ? max-min+1 : sums[left] + sums[right];
}
int main(){
    bool isprime[100000]; memset(isprime, 0xff, sizeof(isprime)); // fill( isprime, true );
    isprime[0] = isprime[1] = false;
    np = 0;
    for(int i=2; i<100000; i++){
        if(isprime[i]){
            primes[np++] = i;
            for(int j=i+i; j<100000; j+=i)
                isprime[j] = false;
        }
    }
    for(int i=1; i<=100000; i++){
        int f=0;
        int number=i;
        for(int j=0; number>1; ++j){
            int p = primes[j];
            if(number%p==0){
                factors[i][f++] = j;
                while(number%p==0)
                    number/=p;
            }
        }
        factors[i][f] = -1;
    }
    for(;;){
        n = in_nextInt();
        k = in_nextInt();
        m = in_nextInt();
        if(n==0)
            break;
        memset(intervals, 0, sizeof(intervals));
        memset(sums     , 0, sizeof(sums     ));
        fill(last, 10000, -1);
        memset(trees, 0, sizeof(trees));
        ll sum = 0LL;
        for(int i=0; i<n; i++){
            sequence[i] = in_nextInt();
            sum += sequence[i];
            for(int f=0; ; f++ ){
                int p = factors[sequence[i]][f];
                if( p<0 )
                    break;
                if( last[p]>=0 && i-last[p]<k ){
                    int lo = max( i, k-1 );
                    int hi = min( last[p]+k-1, n-1 );
                    adjust( lo, hi, 0, n-1, 1, 1 );
                }
                Node*node = newNode(i);
                if( trees[p]==NULL )
                    trees[p] = node;
                else{
                    root = trees[p];
                    insert(root, node);
                    trees[p] = root;
                }
                last[p] = i;
            }
        }
        printf("%d\n", sums[1] );
        for(int i=0; i<m; i++){
            int a = in_nextInt()-1;
            int b = in_nextInt();
            int sa = sequence[a];
            sum += b - sa;
            for( int f=0; ; f++){
                int p = factors[b][f];
                if( p<0 )
                    break;
                inb[p] = true;
            }
            for( int f=0; ; f++){
                int p = factors[sa][f];
                if( p<0 )
                    break;
                ina[p] = true;
                if( inb[p] )
                    continue;
                root = trees[p];
                Node*node = find(root, a);
                if(node->prev!=NULL){
                    int lastp = node->prev->value;
                    if( a-lastp<k ){
                        int lo = max( a, k-1 );
                        int hi = min( lastp+k-1, n-1 );
                        adjust( lo, hi, 0, n-1, 1, -1 );
                    }
                }
                if( node->next!=NULL ){
                    int nextp = node->next->value;
                    if( nextp-a<k ){
                        int lo = max( nextp, k-1 );
                        int hi = min( a+k-1, n-1 );
                        adjust( lo, hi, 0, n-1, 1, -1 );
                    }
                    if( node->prev!=NULL ){
                        int lastp = node->prev->value;
                        if( nextp-lastp<k ){
                            int lo = max( nextp, k-1 );
                            int hi = min( lastp+k-1, n-1 );
                            adjust( lo, hi, 0, n-1, 1, 1 );
                        }
                    }
                }
                delete(root, a);
                trees[p] =  root;
            }
            sequence[a] = b;
            for( int f=0; ; f++ ){
                int p = factors[b][f];
                if( p<0 )
                    break;
                if( ina[p] )
                    continue;
                Node*node = newNode( a );
                if( trees[p]==NULL )
                    trees[p] = node;
                else{
                    root = trees[p];
                    insert(root, node);
                    trees[p] = root;
                }
                if( node->prev!=NULL ){
                    int lastp = node->prev->value;
                    if( a-lastp<k ){
                        int lo = max( a, k-1 );
                        int hi = min( lastp+k-1, n-1 );
                        adjust( lo, hi, 0, n-1, 1, 1 );
                    }
                }
                if( node->next!=NULL ){
                    int nextp = node->next->value;
                    if( nextp-a<k ){
                        int lo = max( nextp, k-1 );
                        int hi = min( a+k-1, n-1 );
                        adjust( lo, hi, 0, n-1, 1, 1 );
                    }
                    if( node->prev!=NULL ){
                        int lastp = node->prev->value;
                        if( nextp-lastp<k ){
                            int lo = max( nextp, k-1 );
                            int hi = min( lastp+k-1, n-1 );
                            adjust( lo, hi, 0, n-1, 1, -1 );
                        }
                    }
                }
            }
            for( int f=0; ; f++ ){
                int p = factors[b][f];
                if( p<0 )
                    break;
                inb[p] = false;
            }
            for( int f=0; ; f++ ){
                int p = factors[sa][f];
                if( p<0 )
                    break;
                ina[p] = false;
            }
            printf("%d\n", sums[1]);
        }
        printf("%lld\n", sum);
        break;
    }
    return 0;
}
