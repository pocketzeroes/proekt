int** reconstructQueue(int** people, int peopleRowSize, int peopleColSize, int* returnSize) {
    if(peopleRowSize<1||peopleColSize<1) {*returnSize=0;return NULL;}
    *returnSize=peopleRowSize;
    int i,j,k,h,**res;
    res=malloc(sizeof(int*)*peopleRowSize);
    for(i=0;i<peopleRowSize;i++){
        res[i]=malloc(sizeof(int)*2);
    }
    for(i=0;i<peopleRowSize;i++){
        h=2147483647;
        for(j=0;j<peopleRowSize;j++){
            if((people[j][1]==0)&&(people[j][0]<h)) { h=people[j][0];k=j;}
        }
        res[i][0]=people[k][0];
        res[i][1]=people[k][1];
        for(j=0;j<i;j++){
            if(res[j][0]>=res[i][0])res[i][1]++;
        }
        people[k][1]=-1;
        for(j=0;j<peopleRowSize;j++){
            if((people[j][1]!=-1)&&(people[j][0]<=people[k][0])) people[j][1]--;
        }
    }
    return res;
}