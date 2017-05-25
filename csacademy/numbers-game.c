#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);
    int numbers[n];
    for(int i=0;i<n;i++)
      scanf("%d", &numbers[i]);

    int cnt=0;
    int last, first;
    last=numbers[0]%10;
    for(int i=1;i<n;i++){
        int this = numbers[i];
        first = this/10;
        if(first==last){}else
          cnt++;
        last = this%10;
    }
    printf("%d\n", cnt);
    return 0;
}
