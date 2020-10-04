typedef struct {
}ParkingSystem;
ParkingSystem*gptr;

int a, b, c;

ParkingSystem*parkingSystemCreate(int _a, int _b, int _c){
    a = _a;
    b = _b;
    c = _c;
    return gptr;
}
bool parkingSystemAddCar(ParkingSystem* obj, int t){
    int*x;
    if(t == 1){
        x = &a;
    }
    else 
        x = t == 2 ? &b : &c;
    if(*x > 0) {
        (*x)--;
        return true;
    }
    else 
        return false;
}
void parkingSystemFree(ParkingSystem* obj) {
    ;
}
