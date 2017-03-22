#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int**pushback(int**array, int *size, int*value) {
    int**output = resizeArray(array, int*, *size + 1);
    output[(*size)++] = value;
    return output;
}
int*pushback1d(int*array, int *size, int value) {
    int*output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}


typedef struct {
    int a;
} Twitter;
Twitter*ptr;
#define IS_FOLLOW_SIZE 512
bool is_follow[IS_FOLLOW_SIZE][IS_FOLLOW_SIZE];
int**fs;
int* fsSz;
void add_user(int userId){
    is_follow[userId][userId] = true;
}
////
Twitter* twitterCreate() {
    fs=NULL;
    fsSz=malloc(sizeof(int));
   *fsSz=0;
    memset(is_follow,0,sizeof(is_follow));
    return ptr;
}
void twitterPostTweet(Twitter* obj, int userId, int tweetId) {
    add_user(userId);
    int*pair=malloc(2*sizeof(int));
    pair[0]=userId;
    pair[1]=tweetId;
    fs=pushback(fs, fsSz, pair);
}
int*twitterGetNewsFeed(Twitter* obj, int userId, int*returnSize){
    int count = 0;
    int*ret=NULL;
    for(int i = *fsSz - 1; i >= 0 && count < 10; --i)
        if( IS_FOLLOW_SIZE > userId && IS_FOLLOW_SIZE > fs[i][0] && is_follow[userId][fs[i][0]] ){
            ret=pushback1d(ret, returnSize, fs[i][1]);
            ++count;
        }
    return ret;
}
void twitterFollow(Twitter* obj, int followerId, int followeeId) {
    add_user(followerId);
    add_user(followeeId);
    is_follow[followerId][followeeId] = true;
}
void twitterUnfollow(Twitter* obj, int followerId, int followeeId) {
    if(followerId == followeeId) 
        return;
    if(IS_FOLLOW_SIZE > followerId && IS_FOLLOW_SIZE > followeeId)
        is_follow[followerId][followeeId] = false;
}
void twitterFree(Twitter* obj) {
    free(fs);
    fs=NULL;
}
#define DEBUG_ON 0
#if DEBUG_ON
int main(){
    int sz;
    Twitter*obj = twitterCreate();                 // null
    twitterPostTweet(obj, 1, 5);                   // null
    int* param_2 = twitterGetNewsFeed(obj, 1,&sz); // 5
    printf("%d\n", param_2[0]);
    twitterFollow   (obj, 1, 2);                   // null
    twitterPostTweet(obj, 2, 6);                   // null
    int* param_3 = twitterGetNewsFeed(obj, 1,&sz); // 6, 5
    twitterUnfollow (obj, 1, 2);                   // null
    int* param_4 = twitterGetNewsFeed(obj, 1,&sz); // 5
    twitterFree     (obj);
}
#endif
    




























