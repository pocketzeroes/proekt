#include<stdio.h>
#include<stdbool.h>

int main(){
    int i,j,k,l;
    int f, c, stars;
    bool star=true;
    scanf("%d %d", &f, &c);
    while(f!=0){
        stars = 0;
        char matriz [f][c];
        for( i=0;i<f;i++){
            getchar();
            for( j=0;j<c;j++){
                scanf("%c", &matriz[i][j]);
            }
        }
        for( i=0;i<f;i++){
            for( j=0;j<c;j++){
                if(matriz[i][j] == 42){
                    for( k=0;k<3;k++){
                        for( l=0;l<3;l++){
                            if(((i+k-1)<f) && ((j+l-1)<c)){
                                if(((i+k-1)>-1) && ((j+l-1)>-1)){
                                    if((matriz[i+k-1][j+l-1] == 42) && !((i+k-1)== i  && (j+l-1)==j)){
                                        star = false;
                                    }
                                }
                            }
                        }
                    }
                    if(star == true){
                        stars++;
                    }
                }
                star= true;
            }
        }
        printf("%d\n", stars);
        scanf("%d %d", &f, &c);
    }
    return 0;
}
