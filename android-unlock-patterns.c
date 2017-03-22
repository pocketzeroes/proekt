inline int merge(int i, int j) {
    return i | (1 << j);
}
inline bool contain(int i, int j) {
    return i & (1 << j);
}
inline int convert(int i, int j) {
    return 3 * i + j;
}
int numberOfPatternsHelper(int m, int n, int level, int used, int i) {
    int number = 0;
    if (level > n)
        return number;
    if (level >= m)
        ++number;
    int x1 = i / 3;
    int y1 = i % 3;
    for (int j = 0; j < 9; ++j) {
        if (contain(used, j))
            continue;
        int x2 = j / 3;
        int y2 = j % 3;
        if (((x1 == x2 && abs(y1 - y2) == 2) || (y1 == y2 && abs(x1 - x2) == 2) || (abs(x1 - x2) == 2 && abs(y1 - y2) == 2)) && !contain(used, convert((x1 + x2) / 2, (y1 + y2) / 2)))
                 continue;
        number += numberOfPatternsHelper(m, n, level + 1, merge(used, j), j);
    }
    return number;
}
int numberOfPatterns(int m, int n) {
    int number = 0;
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 0), 0);
    number += 4 * numberOfPatternsHelper(m, n, 1, merge(0, 1), 1);
    number +=     numberOfPatternsHelper(m, n, 1, merge(0, 4), 4);
    return number;
}


