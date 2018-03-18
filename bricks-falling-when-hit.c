#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void swap(int*nums, int i, int j) {
   int t   = nums[i];
   nums[i] = nums[j];
   nums[j] = t;
}
void reverse(int*nums,int start,int end){
    while( start < end) {
        swap(nums, start, end);
        start++;
        end  --;
    }
}
///////////////////////////
int f[40005],
    s[40005],n,m,N,M,i,j,k,l;
const int dx[4] = {-1,0,1,0},
          dy[4] = {0,-1,0,1};

int get1(int x){
    if(f[x]==x)
        return x;
    return f[x]=get1(f[x]);
}
int get(int x,int y){
    return x*m+y;
}
void merge(int x,int y){
    x=get1(x);
    y=get1(y);
    if(x==y)
        return;
    s[x]+=s[y];
    f[y]=x;
}
int*hitBricks(int**grid, int gridSz, int*grid0szs, int**hits, int hitsSz, int*hits0szs, int*rsz){
    n = gridSz;
    m = grid0szs[0];
    N = n*m;
    M = hitsSz;
    vec ans = newVec();
    for(i=0;i<M;i++)
        grid[hits[i][0]][hits[i][1]]^=2;
    for(i=0;i<=N;i++){
        f[i]=i;
        s[i]=1;
    }
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            if(grid[i][j]==1){
                if(i+1<n&&grid[i+1][j]==1)
                    merge(get(i,j),get(i+1,j));
                if(j+1<m&&grid[i][j+1]==1)
                    merge(get(i,j),get(i,j+1));
                if(!i)
                    merge(N,get(i,j));
            }
    for(i=M-1;~i;i--)
        if(grid[hits[i][0]][hits[i][1]]==3){
            grid[hits[i][0]][hits[i][1]]=1;
            if(!hits[i][0])
                merge(N,get(hits[i][0],hits[i][1]));
            for(j=0;j<4;j++)
                if(hits[i][0]+dx[j]>=0&&hits[i][0]+dx[j]<n&&hits[i][1]+dy[j]>=0&&hits[i][1]+dy[j]<m&&grid[hits[i][0]+dx[j]][hits[i][1]+dy[j]]==1){
                    k=get1(get(hits[i][0]+dx[j],hits[i][1]+dy[j]));
                    if(k==N)
                        break;
                }
            if(j==4&&hits[i][0]){
                ans.ptr = pushback(ans.ptr, &ans.sz, 0);
                for(j=0;j<4;j++)
                    if(hits[i][0]+dx[j]>=0&&hits[i][0]+dx[j]<n&&hits[i][1]+dy[j]>=0&&hits[i][1]+dy[j]<m&&grid[hits[i][0]+dx[j]][hits[i][1]+dy[j]]==1){
                        k=get1(get(hits[i][0]+dx[j],hits[i][1]+dy[j]));
                        merge(k,get(hits[i][0],hits[i][1]));
                    }
                continue;
            }
            for(j=l=0;j<4;j++)
                if(hits[i][0]+dx[j]>=0&&hits[i][0]+dx[j]<n&&hits[i][1]+dy[j]>=0&&hits[i][1]+dy[j]<m&&grid[hits[i][0]+dx[j]][hits[i][1]+dy[j]]==1){
                    k=get1(get(hits[i][0]+dx[j],hits[i][1]+dy[j]));
                    if(k!=N)
                        l+=s[k];
                    merge(N,k);
                }
            ans.ptr = pushback(ans.ptr, &ans.sz, l);
            merge(N,get(hits[i][0],hits[i][1]));
        }
        else
            ans.ptr = pushback(ans.ptr, &ans.sz, 0);
    reverse(ans.ptr, 0, ans.sz-1);
   *rsz=   ans.sz;
    return ans.ptr;
}
