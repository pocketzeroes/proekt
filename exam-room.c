#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))
int *pushback(int *array, int *size, int value) {
    int *output = resizeArray(array, int, *size + 1);
    output[(*size)++] = value;
    return output;
}
typedef struct{
	int*ptr;
	int sz;
}vec;
vec newVec() {
	vec rez;
	rez.ptr = NULL;
	rez.sz  = 0;
	return rez;
}

typedef struct{}ExamRoom; ExamRoom*er;
int num;
int now;
vec store;
void erase(vec*v, int pos){
    for(int i=pos; i < v->sz-1; i++){
        v->ptr[i] = v->ptr[i+1];
    }
    (v->sz)--;
}

ExamRoom*examRoomCreate(int N){
    store = newVec();
    num=N;
    now=0;
    return er;
}
int examRoomSeat(ExamRoom*obj){
    if(now==0){
        now++;
        store.ptr = pushback(store.ptr, &store.sz, 0);
        return 0;
    }
    int ans=num-1,dis=ans - store.ptr[now-1];
    for(int i=now-2;i>=0;i--){
        if((store.ptr[i+1]-store.ptr[i])/2>=dis){
            ans=store.ptr[i]+(store.ptr[i+1]-store.ptr[i])/2;
            dis=(store.ptr[i+1]-store.ptr[i])/2;
        }
    }
    if(store.ptr[0]>=dis)
        ans=0;
    store.ptr = pushback(store.ptr, &store.sz, ans);
    now++;
    for(int i=now-2;i>=0;i--){
        if(store.ptr[i]<store.ptr[i+1])
            break;
        int tmp=store.ptr[i];
        store.ptr[i]=store.ptr[i+1];
        store.ptr[i+1]=tmp;
    }
    return ans;
}
void examRoomLeave(ExamRoom*obj, int p){
    for(int i=0;i<now;i++){
        if(store.ptr[i]==p){
            erase(&store, i);
            break;
        }
    }
    now--;
}
void examRoomFree(ExamRoom*obj){
    return;
}
