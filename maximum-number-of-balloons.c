int count(char*k, char c){
    int cnt=0;
    for(int z=0;k[z];z++){char chr=k[z];
        if(chr==c)
            cnt++;
    }
    return cnt;
}
int maxNumberOfBalloons(char*text){
    int answer = count(text, 'b');
    answer = fmin(answer, count(text, 'a'));
    answer = fmin(answer, count(text, 'l') / 2);
    answer = fmin(answer, count(text, 'o') / 2);
    answer = fmin(answer, count(text, 'n'));
    return answer;
}
