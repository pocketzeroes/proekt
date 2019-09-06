#include<stdio.h>
#include<math.h>
 
int main(){
	int X, Y, N;
	float r;
	char can_pay;
	double balance, mr;
	while ( scanf("%d %d %d %f", &X, &Y, &N, &r) == 4 ){
		if (!X)
      break;
		mr = r/100/12;
		can_pay = 1;
		if (X*mr >= Y){
			can_pay = 0; 
		}
    else if (r < 0.001) {
			if( Y* N*12 < X )
				can_pay = 0; 
		}
		else {
			balance = (X - Y/mr) * pow(1+mr, N*12) + Y/mr;
			if(balance > 0)
        can_pay = 0;
		}
		if(can_pay)
      printf("YES\n");
		else
      printf("NO\n");
	}
	return 0;
}
