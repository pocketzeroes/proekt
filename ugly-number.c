
    bool isUgly(int num) {
        if (num == 0) {
            return false;
        }
        for (int i=2;i<=5;i++) {
            if(i==2||i==3||i==5){
              while (num % i == 0) {
                num /= i;
              }
            }
        }
        return num == 1;
    }