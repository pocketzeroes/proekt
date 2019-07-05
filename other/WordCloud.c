#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>
int min(int a,int b){return a<b?a:b;}
int max(int a,int b){return a>b?a:b;}

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

enum{ PAD   = 10  };
enum{ MIN_C = 5   };
enum{ MAX_C = 1000};
enum{ MAX_W = 5000};
enum{ MAX_N = 1000};


typedef struct{
    int wordlength, 
        count, 
        width, 
        height;
}item;

item box[MAX_N];

int bceil(int num, int denom){
    return(num/denom + (num % denom > 0 ? 1 : 0));
}
int main(){
    int trial=0;
    while(1){
        int W, N;
        scanf("%d %d", &W, &N);
        if (W == 0) 
            break;
        int maxC = 0;
        for (int j=0; j<N; j++) {
            char*S=getstr();
            int C;
            scanf("%d", &C);
            box[j].wordlength = strlen(S);
            box[j].count = C;
            maxC = max(maxC, C);
        }
        for(int j=0; j<N; j++){
            box[j].height = 8 + bceil(40*(box[j].count-4), maxC-4);
            box[j].width = bceil(9*box[j].wordlength*box[j].height, 16);
        }
        int total = 0;
        int lineWidth  = box[0].width;
        int lineHeight = box[0].height;
        for(int j=1; j<N; j++){
            if( lineWidth +  PAD + box[j].width <= W){
                lineWidth += PAD + box[j].width;
                lineHeight = max(lineHeight, box[j].height);
            }
            else{
                total += lineHeight;
                lineHeight = box[j].height;
                lineWidth  = box[j].width;
            }
        }
        total += lineHeight;
        printf("CLOUD %d: %d\n", ++trial, total);
    }
    return 0;
}
