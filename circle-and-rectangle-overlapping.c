int dist(int x1, int y1, int x2, int y2){
    return (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
}
bool checkOverlap(int radius, int x_center, int y_center, int x1, int y1, int x2, int y2) {
    if(x1 <= x_center && x_center <= x2 && y1 <= y_center && y_center <= y2) return true;
    for(int x = x1; x <= x2; x++)
        if(dist(x, y1, x_center, y_center) <= radius * radius) return true;
    for(int x = x1; x <= x2; x++)
        if(dist(x, y2, x_center, y_center) <= radius * radius) return true;
    for(int y = y1; y <= y2; y++)
        if(dist(x1, y, x_center, y_center) <= radius * radius) return true;
    for(int y = y1; y <= y2; y++)
        if(dist(x2, y, x_center, y_center) <= radius * radius) return true;
    return false;
}
