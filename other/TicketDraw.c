#include<stdio.h>
#include<stdlib.h>
#include<math.h>
typedef long long ll;
enum{ MaxLength=101};

int main(){
  int NumberOfCases;
  ll value_M, temp_value_M, value_Z, temp_value_Z;
  ll suffix_M, suffix_Z, powers;
  int M[MaxLength], Z[MaxLength];
  int r;
  ll F[MaxLength], S[MaxLength];
  int c,n,i,j,k,digit;
  ll temp;
  scanf("%d", &NumberOfCases);
  for (c = 1; c <= NumberOfCases; c++) {
    scanf("%Ld%Ld%d", &value_M, &value_Z, &r);
    value_M--;
    n=0;
    temp_value_M=value_M;
    temp_value_Z=value_Z;
    do {
      n++;
      digit =(int)( temp_value_M % 10);
      M[n] = digit;
      temp_value_M /= 10;
      digit =(int)( temp_value_Z % 10);
      Z[n] = digit;
      temp_value_Z /= 10;
    } while( temp_value_M > 0);
    for (k = 0; k <= n; k++){
      temp=0;
      for (i = 1; i <= r; i++) {
        if ((k-i) == -1) temp = temp+1;
        if ((k-i) == 0)  temp = temp+9;
        if ((k-i) > 0)   temp = temp+9*F[k-i];
      }
      F[k]=temp;
    }
    powers=10;
    for (i = 1; i <= r-1; i++) {
      suffix_M = (ll)( value_M % powers);
      S[i] = (suffix_M + 1);
      powers=powers*10;
    }
    suffix_M = (ll)( value_M % powers);
    suffix_Z = (ll)( value_Z % powers);
    if (suffix_M < suffix_Z) S[r] = (suffix_M + 1);
    else S[r]= (suffix_M + 1) - 1;
    for (k = r+1; k <= n; k++) {
      temp=0;
      if (Z[k] > M[k]) temp = M[k]*F[k-1] + S[k-1];
      if (Z[k] < M[k]){
        temp = (M[k]-1)*F[k-1] + S[k-1];
        for (i = 2; i <= r; i++) {
          temp = temp + 9*F[k-i];
        }
      }
      if (Z[k] == M[k]){
        temp = M[k]*F[k-1];
        for (i = 2; i <= r; i++) {
          if (Z[k-i+1] > M[k-i+1]) {
            temp = temp + M[k-i+1]*F[k-i] + S[k-i];
            break;
          }
          if (Z[k-i+1] < M[k-i+1]) {
            temp = temp + (M[k-i+1]-1)*F[k-i]+S[k-i];
            for (j = i+1; j <= r; j++) {
              temp = temp + 9*F[k-j];
            }
            break;
          }
          if (Z[k-i+1] == M[k-i+1]) {
            temp = temp + M[k-i+1]*F[k-i];
          }
        }
      }
      S[k]=temp;
    }
    printf("%Ld\n", value_M+1-S[n]);
  }
  return 0;
}
