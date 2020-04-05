int numSteps(char*s){
    char*array = s;
    int j = strlen(array)-1;
    int answer = 0;
    char carry = '0';
    while(j > 0){
        if (array[j] == '1' && carry == '0') {
            answer++;
            carry = '1';
        }
        else if (array[j] == '0' && carry == '1')
            answer++;
        answer++;
        j--;
    }
    if (carry == '1')
        answer++;
    return answer;
}
