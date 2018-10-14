int min(int a,int b){return a<b?a:b;}
int minAddToMakeValid(char*s){
    int n = strlen(s);
    int h = 0;
    int mini = 0;
    for(int i = 0;i < n;i++){
        if(s[i] == '('){
            h++;
        }
        else{
            h--;
        }
        mini = min(mini, h);
    }
    h += -mini;
    return -mini + abs(h);
}
