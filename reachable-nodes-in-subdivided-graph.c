#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))
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
vec newVec(){
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}
void fill(int*arr,int sz, int val){
  for(int i=0;i<sz;i++)
    arr[i]=val;
}

int reachableNodes(int**v, int vSz, int*edgesColSizes, int m, int n){
    int  dis[n]; fill(dis, n, -1);
    vec  hv [n]; memset(hv , 0, sizeof(hv ));
    bool vis[n]; memset(vis, 0, sizeof(vis));
    int lll[vSz];memset(lll, 0, sizeof(lll));
    int rrr[vSz];memset(rrr, 0, sizeof(rrr));
    int ans = 0;
    dis[0] = 0;
    for(int i = 0; i < vSz; i++){
        hv[v[i][0]].ptr = pushback(hv[v[i][0]].ptr, &hv[v[i][0]].sz, i);
        hv[v[i][1]].ptr = pushback(hv[v[i][1]].ptr, &hv[v[i][1]].sz, i);
    }
    while(1){
        int tmp = -1;
        for (int i = 0; i < n; i++)
            if (!vis[i] && dis[i] != -1 && (tmp == -1 || dis[i] < dis[tmp]))
                tmp = i;
        if (tmp == -1)
            break;
        vis[tmp] = 1;
        for(int z=0;z<hv[tmp].sz;z++){int i = hv[tmp].ptr[z];
            int to = v[i][0] == tmp ? v[i][1] : v[i][0];
            int dd = dis[tmp] + v[i][2] + 1;
            if (dis[to] == -1 || dd < dis[to])
                dis[to] = dd;
        }
    }
    for (int i = 0; i < n; i++)
        if (vis[i] && dis[i] <= m) {
            ans++;
            for(int z=0;z<hv[i].sz;z++){int j = hv[i].ptr[z];
                if (i == v[j][0])
                    lll[j] = m - dis[i];
                else
                    rrr[j] = m - dis[i];
            }
        }
    for (int i = 0; i < vSz; i++)
        ans += min(v[i][2], lll[i] + rrr[i]);
    return ans;
}
