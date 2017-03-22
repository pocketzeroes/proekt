bool validIPv4(char*IP) {
    int begin = 0, end = 0, cnt = 0;
    int IPsize=strlen(IP);
    while (end < IPsize) {
        int leadingZeroCount = 0, num = 0;
        while (end < IPsize && isdigit(IP[end])) {
            num = num * 10 + IP[end] - '0';
            if (IP[end] == '0' && num == 0) leadingZeroCount++;
            if ((leadingZeroCount > 0 && num != 0)
            || leadingZeroCount > 1
            || end - begin + 1 > 3
            || num > 255) return false;
            ++end;
        }
        if (end == begin) return false;
        ++cnt;
        if (cnt <= 3) {
            if (end >= IPsize || IP[end] != '.') return false;
            begin = ++end;
        } else {
            if (end != IPsize) return false;
        }
    }
    return cnt == 4;
}
bool validIPv6(char*IP) {
    int cnt = 0, begin = 0, end = 0;
    int IPsize=strlen(IP);
    while (end < IPsize) {
        while (end < IPsize && isalnum(IP[end])) {
            if ((IP[end] > 'f' && IP[end] <= 'z')
            || (IP[end] > 'F' && IP[end] <= 'Z')
            || end - begin + 1 > 4) return false;
            ++end;
        }
        if (begin == end) return false;
        ++cnt;
        if (cnt <= 7) {
            if (end >= IPsize || IP[end] != ':') return false;
            begin = ++end;
        } else {
            if (end != IPsize) return false;
        }
    }
    return cnt == 8;
}
char* validIPAddress(char* IP) {
    if (validIPv4(IP)) return "IPv4";
    if (validIPv6(IP)) return "IPv6";
    return "Neither";
}
