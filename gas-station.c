int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    int total = 0;
    int sum   = 0;
    int j     =-1;
    for(int i = 0; i < gasSize; ++i) {
        total += gas[i] - cost[i];
        sum   += gas[i] - cost[i];
        if(sum < 0) {
            sum = 0;
            j   = i;
        }
    }
    return (total >= 0) ? j + 1 : -1;
}
