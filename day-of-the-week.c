char*S[7]={"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

char*dayOfTheWeek(int day, int month, int y) {
    if (month < 3) {
        y--;
        month += 12;
    }
    int w = (y + y / 4 - y / 100 + y / 400 + (13 * month + 8) / 5 + day) % 7;
    return S[w];
}
