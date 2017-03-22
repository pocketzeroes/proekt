int* findMinHeightTrees(int n, int** edges, int rSize, int cSize, int* returnSize)
{
    int* arr = (int*)malloc(sizeof(int)*n);
    *returnSize = 0;
    if(n == 1) 
    {
        *returnSize += 1;
        arr[*returnSize-1] = 0;
        return arr;
    }
    int** graph = (int**)malloc(sizeof(int*)*n);
    for(int i = 0; i < n; i++)
        graph[i] = (int*)malloc(sizeof(int));
    int* colSizes = (int*)malloc(sizeof(int)*n);
    memset(colSizes, 0, sizeof(int)*n);
    for(int i = 0; i < rSize; i++) 
    {
        int begin = edges[i][0];
        int end = edges[i][1];
        colSizes[begin]++;
        graph[begin] = (int*)realloc(graph[begin], sizeof(int)*colSizes[begin]);
        graph[begin][colSizes[begin]-1] = end;
        colSizes[end]++;
        graph[end] = (int*)realloc(graph[end], sizeof(int)*colSizes[end]);
        graph[end][colSizes[end]-1] = begin;
    }
    int* degrees = (int*)malloc(sizeof(int)*n);
    for(int i = 0; i < n; i++) 
    {
        degrees[i] = colSizes[i]; 
        if(colSizes[i] == 1)
        {
            *returnSize += 1;
            arr[*returnSize-1] = i;
        }
    }
    int count = n; 
    int* nextLevel = (int*)malloc(sizeof(int)*n);
    int next = 0;
    while(count > 2) 
    {
        for(int i = 0; i < *returnSize; i++)
        {
            int end = arr[i];
            count--; 
            for(int k = 0; k < colSizes[end]; k++) 
            {
                int begin = graph[end][k];
                degrees[begin]--;
                if(degrees[begin] == 1) 
                    nextLevel[next++] = graph[end][k]; 
            }
        }
        *returnSize = next; 
        next = 0;
        int *t=arr; arr=nextLevel; nextLevel=t;
    }
    return arr;
}



