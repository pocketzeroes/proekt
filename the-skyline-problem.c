int** getSkyline(int** buildings, int buildingsRowSize, int buildingsColSize, int* returnSize) {
    *returnSize=0;
    if(0>=buildingsRowSize){
        return 0;
    }
    int **ret;
    if(1==buildingsRowSize){
        ret=malloc(sizeof(int*)*2);
        int *t=malloc(sizeof(int)*2);
        t[0]=buildings[0][0];
        t[1]=buildings[0][2];
        ret[0]=t;
        t=malloc(sizeof(int)*2);
        t[0]=buildings[0][1];
        t[1]=0;
        ret[1]=t;
        *returnSize=2;
        return ret;
    }
    int mid= buildingsRowSize/2;
    int l_rsize=0;
    int **l_ret=getSkyline(buildings,mid,buildingsColSize,&l_rsize);
    int r_rsize=0;
    int **r_ret=getSkyline(buildings+mid,buildingsRowSize-mid,buildingsColSize,&r_rsize);
    ret=malloc(sizeof(int*)*(l_rsize+r_rsize));
    int lp=0;
    int rp=0;
    int lh=-1;
    int rh=-1;
    while(lp<l_rsize && rp<r_rsize){
        int *l_pot=l_ret[lp];
        int *r_pot=r_ret[rp];
        if(l_pot[0]<r_pot[0]){
            lh=l_pot[1];
            l_pot[1]= lh>rh? lh :rh;
            if(0==*returnSize || l_pot[1]!=ret[*returnSize-1][1]){
                ret[*returnSize]=l_pot;
                ++(*returnSize);
            }else{
                free(l_pot);
            }
            ++lp;
        } else if(l_pot[0]>r_pot[0]){
            rh=r_pot[1];
            r_pot[1]= rh>lh? rh :lh;
            if(0==*returnSize || r_pot[1]!=ret[*returnSize-1][1]){
                ret[*returnSize]=r_pot;
                ++(*returnSize);
            }else{
                free(r_pot);
            }
            ++rp;
        } else {
            lh=l_pot[1];
            rh=r_pot[1];
            l_pot[1]= lh>rh? lh :rh;
            if(0==*returnSize || l_pot[1]!=ret[*returnSize-1][1]){
                ret[*returnSize]=l_pot;
                ++(*returnSize);
            }else{
                free(l_pot);
            }
            free(r_pot);
            ++lp;
            ++rp;
        }
    }
    while(lp<l_rsize){
        int *l_pot=l_ret[lp];
        if(0==*returnSize || l_pot[1]!=ret[*returnSize-1][1]){
            ret[*returnSize]=l_pot;
            ++(*returnSize);
        }else{
            free(l_pot);
        }
        ++lp;
    }
    while(rp<r_rsize){
        int *r_pot=r_ret[rp];
        if(0==*returnSize || r_pot[1]!=ret[*returnSize-1][1]){
            ret[*returnSize]=r_pot;
            ++(*returnSize);
        }else{
            free(r_pot);
        }
        ++rp;
    }
    free(l_ret);
    free(r_ret);
    return ret;
}




