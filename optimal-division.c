
char*optimalDivision(int*nums, int numsSize){
    char buff[32];
    if (numsSize == 1){
        sprintf(buff, "%d", nums[0]);
        return strdup(buff);
    }
    if(numsSize == 2){
        char*ptr;
        asprintf(&ptr, "%d/%d",nums[0],nums[1]);
        return ptr;
    }
    char*ans;
    asprintf(&ans, "%d/", nums[0]);
    char*tmp;
    asprintf(&tmp, "%d", nums[1]);
    for(int i = 2; i < numsSize; ++i){
        char*pp;
        asprintf(&pp,"%s/%d", tmp, nums[i]);
        free(tmp);
        tmp=pp;
    }
    char*rez;
    asprintf(&rez,"%s(%s)", ans, tmp);
    return rez;
}
