bool isValid(char*s){
    int stack[20005] = {0};
    int p = 1;
    for(int z=0;s[z];z++){char c = s[z];
        if(p == 0){
            if(c == 'a')
                stack[p++] = 1;
            else
                return false;
        }
        else if(stack[p-1] == 0){
            if(c == 'a')
                stack[p-1]++;
            else
                return false;
        }
        else if(stack[p-1] == 1){
            if(c == 'a'){
                stack[p] = 1;
                p++;
            }
            else if(c == 'b')
                stack[p-1]++;
            else
                return false;
        }
        else{
            if(c == 'a'){
                stack[p] = 1;
                p++;
            }
            else if(c == 'c')
                p--;
            else
                return false;
        }
    }
    return p == 0;
}
