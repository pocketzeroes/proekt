int*helper(char*s, int start, int end){
    int a = 0;
    int b = 0;
    int i = start;
    while(i<end){
        int sign = 1;
        if(s[i]=='-'){
            sign = -1;
            i++;
        }
        else if(s[i]=='+')
            i++;
        int num = 0;
        int j = i;
        while(i<end&&isdigit(s[i])){
            num = 10*num + s[i]-'0';
            i++;
        }
        if(i<end&&s[i]=='x'){
            if(num==0&&i==j)
                a+=sign;
            else
                a+=sign*num;
            i++;
        }
        else
            b+=sign*num;
    }
    int*rv=malloc(2*sizeof(int));
    rv[0]=a;
    rv[1]=b;
    return rv;
}
char*solveEquation(char*equation){
    int n = strlen(equation);
    int i = 0;
    while(equation[i]!='=')
        i++;
    int*left  = helper(equation,0  ,i);
    int*right = helper(equation,i+1,n);
    int a = left [0]-right[0];
    int b = right[1]-left [1];
    if(a==0){
        if(b==0)
            return "Infinite solutions";
        else
            return "No solution";
    }
    else{
        char*rv=NULL;
        asprintf(&rv, "x=%d", b/a);
        return rv;
    }
}


















































