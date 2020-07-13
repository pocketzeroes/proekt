#pragma GCC optimize "-O3"
#pragma GCC option("arch=native","tune=native","no-zero-upper")
#pragma GCC target("avx")
struct mygraph{
    double next;
    double val;
}mygraph;
void help(int n, struct mygraph** graph, int index, int end, double *state, double current, double *xx,int *col){
    if(current<=0.00005)
        return;
    if(state[index]>=current){
        return;
    }
    state[index] = current;
    if(index == end){
        if(*xx<current)
            *xx = current;
        return ;
    }
    int i;
    for(i=0;i<col[index];i++){
        help(n, graph, graph[index][i].next, end, state, current*graph[index][i].val, xx,col);
    }
}
double maxProbability(int n, int** edges, int edgesSize, int* edgesColSize, double* succProb, int succProbSize, int start, int end){
    double *state = (double*)calloc(sizeof(double) , n);
    struct mygraph **graph = ( struct mygraph**)calloc(sizeof( struct mygraph*), n);
    int *col  = (int*)calloc(sizeof(int),n);
    int i;
    for(i=0;i<edgesSize;i++){
        int temp0 = edges[i][0];
        int temp1 = edges[i][1];
        if(col[temp0]==0){
            graph[temp0] = ( struct mygraph*)malloc(sizeof( struct mygraph) );
        }
        else
            graph[temp0] = ( struct mygraph*)realloc(graph[temp0],sizeof( struct mygraph) *(1+col[temp0]));
        if(col[temp1]==0){
            graph[temp1] = ( struct mygraph*)malloc(sizeof( struct mygraph));
        }
        else
            graph[temp1] = ( struct mygraph*)realloc(graph[temp1],sizeof( struct mygraph) *(1+col[temp1]));
        graph[temp0][col[temp0]].next=temp1;
        graph[temp0][col[temp0]++].val  = succProb[i];
        graph[temp1][col[temp1]].next=temp0;
        graph[temp1][col[temp1]++].val  = succProb[i];
    }
    double max=-1;
    help(n, graph, start, end, state, 1, &max,col);
    return max==-1?0:max;
}
