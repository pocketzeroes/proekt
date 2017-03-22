int majorityElement(int* num,int numSz) {
    int major=num[0], count = 1;
    for(int i=1; i<numSz;i++){
        if(count==0){
            count++;
            major=num[i];
        }else if(major==num[i]){
            count++;
        }else count--;
        
    }
    return major;
}
