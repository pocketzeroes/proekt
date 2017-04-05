#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
const int kMaxPos = 1e9;
const int kMaxN = 1e5;

int NumUpgrades(int*positions,int positionsSz,int distance){
    int num_upgrades = 1;
    int mid_position = 0, has_mid = 0;
    int left_position = positions[0];
    int last_pos = 0;
    for(int i=0;i<positionsSz;i++){
        int pos = positions[i];
        while (1) {
            if (has_mid) {
                if (mid_position + distance >= pos) 
                    break;
                else {
                    left_position = pos;
                    has_mid = false;
                    mid_position = 0;
                    num_upgrades ++;
                }
            } 
            else {
                if (left_position + distance >= pos) 
                    break;
                else {
                    mid_position = last_pos;
                    has_mid = true;
                }
            }
        }
        last_pos = pos;
    }
    return num_upgrades;
}
int cmp(const void*pa,const void*pb){
  int*a=(int*)pa;
  int*b=(int*)pb;
  return a[0]-b[0];
}
int main() {
    int n, max_num_upgrades; 
    scanf("%d %d", &n, &max_num_upgrades);
    int positions[n];
    for(int i=0;i<n;i++)
      scanf("%d", &positions[i]);
    qsort(positions, n,sizeof(int),cmp);
    int result = -1;
    for (int p = 29; p >= 0; p--)
        if (NumUpgrades(positions,n, result + (1 << p)) > max_num_upgrades) 
            result += (1 << p);
    printf("%d", 1 + result);
    return 0;
}

























