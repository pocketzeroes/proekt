char* toHex(int num) {
    char*ptr;
    asprintf(&ptr,"%x",num);
    return ptr;
}
