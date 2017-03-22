inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int findMinMoves(int*machines,int machinesSz) {
    int sum =0;for( int i=0;i<machinesSz;i++)sum+=machines[i];
    if (sum % machinesSz != 0) {
        return -1;
    }
    int result = 0, target = sum / machinesSz, curr = 0;
    for( int i=0;i<machinesSz;i++){
        int n=machines[i];
        curr += n - target;
        result = max(result, max(n - target, abs(curr)));
    }
    return result;
}
