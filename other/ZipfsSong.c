#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<assert.h>
#include<stdbool.h>
#include<limits.h>

char buff[1000000];
char*getstr(){
  scanf("%s", &buff);
  return strdup(buff);
}

typedef struct{
  double quality;
  char*  name;
  int    num;
}Song;
Song newSong(double q, char*n, int i){
  return(Song){q, n, i};
}
int cmpS(const void*pa, const void*pb){
  Song*t=(Song*)pa;
  Song*s=(Song*)pb;
  if(t->quality > s->quality)
    return 1;
  else if(t->quality == s->quality) 
    return(t->num < s->num) ? 1 : -1;
  else
    return -1;
}
int main(){
  char*name;
  int n, m;
  double quality, 
         played = 0.;
  scanf("%d %d", &n, &m);
  Song songs[n];
  for(int i=0; i<n; i++){
    scanf("%lf", &played);
    name    = getstr();
    quality = played * (i + 1);
    songs[i] = newSong(quality, name, i);
  }
  qsort(songs, n, sizeof(Song), cmpS);
  for(int i = n-1; i>=n-m; i--)
    printf("%s\n", songs[i].name);
  return 0;
}
