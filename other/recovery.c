#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

void fill(char*arr, int sz, char val){
    for(int i=0; i<sz; i++)
        arr[i] = val;
}
char buff[100000];
int main(){
    scanf("%s", &buff);
    char*rows; rows=strdup(buff);
    scanf("%s", &buff);
    char*cols; cols=strdup(buff);
    int n = strlen(rows);
    int m = strlen(cols);
    char matrix[n][m];
    for( int i=0; i<n; i++ )
        fill( matrix[i], m, '1');
    char rowparity = (m%2==0) ? '0' : '1';
    char colparity = (n%2==0) ? '0' : '1';
    bool rowok[n]; memset(rowok, 0, sizeof(rowok));
    int rowcount = 0;
    for( int i=0; i<n; i++ ){
        rowok[i] = (rows[i]==rowparity);
        if( !rowok[i] )
            ++rowcount;
    }
    bool colok[m]; memset(colok, 0, sizeof(colok));
    int colcount = 0;
    for( int j=0; j<m; j++ ){
        colok[j] = (cols[j]==colparity);
        if( !colok[j] )
            ++colcount;
    }
    bool solved = false;
    if( rowcount%2 == colcount%2 ){
        solved = true;
        if( rowcount>colcount ){
            for( int i=0, c=rowcount-colcount; i<n && c>0; i++ )
                if( !rowok[i] ){
                    matrix[i][0] = '0';
                    rowok[i] = true;
                    --c;
                }
        }
        else{
            for( int j=0, c=colcount-rowcount; j<m && c>0; j++ )
                if( !colok[j] ){
                    matrix[0][j] = '0';
                    colok[j] = true;
                    --c;
                }
        }
        for( int i=0; i<n; i++ )
            for( int j=0; j<m; j++ ){
                if( !rowok[i] && !colok[j] ){
                    matrix[i][j] = '0';
                    rowok[i] = true;
                    colok[j] = true;
                }
            }
    }
    if( solved ){
        for(int i=0; i<n; i++){
          for(int j=0; j<m; j++)
            printf("%c", matrix[i][j]);
          puts("");
        }
    }
    else
        puts("-1");
    return 0;
}
