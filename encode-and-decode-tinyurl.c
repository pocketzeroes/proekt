char*table[1024];
int tableLen=0;
char* encode(char* longUrl) {
    table[tableLen]=strdup(longUrl);
    char*ptr;
    asprintf(&ptr,"%d",tableLen++);
    return ptr;
}
char* decode(char* shortUrl) {
    int index=atoi(shortUrl);
    return table[index];
}
