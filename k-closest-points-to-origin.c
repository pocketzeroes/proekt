int cmp(const void * a, const void * b){
   return ( *(int*)a - *(int*)b );
}
int dist(int*point) {
    return point[0] * point[0] + point[1] * point[1];
}
int**kClosest(int**points, int pointsSz, int*points0sz, int K, int**colszs, int*rsz){
    int N = pointsSz;
    int dists[N];
    for(int i=0; i<N; ++i)
        dists[i] = dist(points[i]);
    qsort(dists, N, sizeof(int), cmp);
    int distK = dists[K-1];
    int**ans = calloc(K, sizeof(int*));
    for(int i=0; i<K; i++)
        ans[i] = calloc(2, sizeof(int));
    int t = 0;
    for(int i=0; i<N; ++i)
        if(dist(points[i]) <= distK)
            ans[t++] = points[i];
   *colszs = points0sz;
   *rsz = K;
    return ans;
}
