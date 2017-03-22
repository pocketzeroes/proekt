bool canFinish(int numCourses, int** prerequisites, int prerequisitesRowSize, int prerequisitesColSize){
    int **graph   =(int **)calloc(numCourses,sizeof(int*));
    int *indegree =(int  *)calloc(numCourses,sizeof(int ));
    int *outdegree=(int  *)calloc(numCourses,sizeof(int ));
    for (int i=0;i<prerequisitesRowSize;i++){
        indegree [prerequisites[i][0]]++;
        outdegree[prerequisites[i][1]]++;
        int prenode=prerequisites[i][1];
        graph[prenode]=(int *)realloc(graph[prenode], outdegree[prenode]*sizeof(int));
        graph[prenode][outdegree[prenode]-1]=prerequisites[i][0];
    }
    int* next    =(int *)calloc(0,sizeof(int));
    int numNext  =0;
    int numResult=0;
    for (int i=0;i<numCourses;i++){
        if (indegree[i]==0){
            numNext++;
            next=(int *)realloc(next, numNext*sizeof(int*));
            next[numNext-1]=i;
        }
    }
    if (numNext==0) 
        return false;
    while(numResult<numCourses){ 
        if (numNext==0) 
            return false;
        int StartNode = numResult;
        int endNode   = numNext + numResult;
        for (int i=StartNode;i<endNode;i++){ 
            int currentcol=next[i];
            numResult++;
            numNext--;
            for (int j=0;j<outdegree[currentcol];j++){
                indegree[graph[currentcol][j]]--;
                if (indegree[graph[currentcol][j]]==0){
                    numNext++;
                    next=(int *)realloc(next, (numResult+numNext)*sizeof(int*));
                    next[numResult+numNext-1]=graph[currentcol][j];
                }
            }
        }
    }
    return true;
}















