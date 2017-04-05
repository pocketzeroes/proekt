const int inf = 0x3f3f3f3f;
inline int min(int a,int b){return a<b?a:b;}
inline int max(int a,int b){return a>b?a:b;}

int main(){
    int n; 
    scanf("%d", &n);
    int elements [n];     memset(elements,0,sizeof(elements));
    int right_min[n + 1]; for(int i=0;i<n+1;i++)right_min[i]=inf;
    for(int i = 0; i < n; i++){
        int x;
        scanf("%d ", &x);
        elements[i] = x;
    }
    for (int i = n - 1; i >= 0; i--){
        right_min[i] = min(right_min[i + 1], elements[i]);
    }
    int answer = 0;
    for (int current_max = elements[0], i = 0; i < n; i++){
        current_max = max(current_max, elements[i]);
        answer += current_max <= right_min[i + 1];
    }
    printf("%d", answer);
    return 0;
}

