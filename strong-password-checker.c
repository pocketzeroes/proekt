inline int max(int x, int y) {
    if (x > y) return x;
    return y;
}
inline int min(int x, int y) {
    if (x < y) return x;
    return y;
}
int strongPasswordChecker(char* s) {
    int len = strlen(s);
    int del, rep, type = 0, result, i, j, temp;
    int *part;
    int partnum = 0;
    if (len <= 3)
    {
        return 6-len;
    }
    else if (len <= 4)
    {
        for (i = 0; i < len; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'Z') type |= 16;
            else if (s[i] >= 'a' && s[i] <= 'z') type |= 8;
            else if (s[i] >= '0' && s[i] <= '9') type |= 4;
        }
        return max(6-len, 3-((type>>4)&1)-((type>>3)&1)-((type>>2)&1));
    }
    else if (len == 5)
    {
        for (i = 0; i < len; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'Z') type |= 16;
            else if (s[i] >= 'a' && s[i] <= 'z') type |= 8;
            else if (s[i] >= '0' && s[i] <= '9') type |= 4;
        }
        if (s[0] == s[1] && s[0] == s[2] && s[0] == s[3] && s[0] == s[4]) return max(2, 3-((type>>4)&1)-((type>>3)&1)-((type>>2)&1));
        else return max(1, 3-((type>>4)&1)-((type>>3)&1)-((type>>2)&1));
    }
    else if (len > 20)
    {
        for (i = 0; i < len; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'Z') type |= 16;
            else if (s[i] >= 'a' && s[i] <= 'z') type |= 8;
            else if (s[i] >= '0' && s[i] <= '9') type |= 4;
        }
        part = (int*)malloc(sizeof(int)*len);
        i = 0;
        while (i < len)
        {
            j = i;
            while (j < len && s[i] == s[j])
            {
                j++;
            }
            if (j-i >= 3) part[partnum++] = j-i;
            i = j;
        }
        result = del = len-20;
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < partnum; j++)
            {
                if (part[j] % 3 == i)
                {
                    if (del > i)
                    {
                        del -= (i+1);
                        part[j] -= (i+1);
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
        if (del > 0)
        {
            for (i = 0; i < partnum; i++)
            {
                temp = min(del, part[i]-2);
                del -= temp;
                part[i] -= temp;
                if (del <= 0) break;
            }
        }
        int rep = 0;
        for (i = 0; i < partnum; i++)
        {
            rep += part[i]/3;
        }
        rep += 3-min(3, ((type>>4)&1)+((type>>3)&1)+((type>>2)&1)+min(3, rep));
        result += rep;
        return result;
    }
    else
    {
        for (i = 0; i < len; i++)
        {
            if (s[i] >= 'A' && s[i] <= 'Z') type |= 16;
            else if (s[i] >= 'a' && s[i] <= 'z') type |= 8;
            else if (s[i] >= '0' && s[i] <= '9') type |= 4;
        }
        part = (int*)malloc(sizeof(int)*len);
        i = 0;
        while (i < len)
        {
            j = i;
            while (j < len && s[i] == s[j])
            {
                j++;
            }
            if (j-i >= 3) part[partnum++] = j-i;
            i = j;
        }
        int rep = 0;
        for (i = 0; i < partnum; i++)
        {
            rep += part[i]/3;
        }
        rep += 3-min(3, ((type>>4)&1)+((type>>3)&1)+((type>>2)&1)+min(3, rep));
        result = rep;
        return result;
    }
}











