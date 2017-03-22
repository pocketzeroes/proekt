int magicalString(int n) {
    if(n == 0) return 0;
    int result = 1;
    int i = 1, j = 1, k = 1, h = 1;
    int* string = malloc(100000 * sizeof(int));
    string[0] = 1;
    while(k < n){
        if(i == 1){
            if(j == 1){
                i = 2;
            }
            else{
                i = 1;
                result++;
            }
        }
        else{
            if(j == 1){
                i = 1;
                result++;
            }
            else{
                i = 2;
            }            
        }
        string[k] = i;
        k++;
        j--;
        if(j == 0){
            j = string[h];
            h++;
        }
    }
    return result;
}