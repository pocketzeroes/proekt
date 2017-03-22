int stck[65535],sum[65535];

int largestRectangleArea(int* hgt, int hgtsz) {
    int top = 0,ret = hgt[0];
    stck[top++] = 0;
    for(int i = 1; i <= hgtsz; i ++)
    {
        int now = (i == hgtsz) ? 0:hgt[i];
        while(top && now < hgt[stck[top-1]])
        {
            int h = hgt[stck[--top]];
            int width = (top?i-1 - stck[top-1] : i);
            int tmp = h*width;
            if(tmp > ret)
                ret  = tmp;
        }
        stck[top++] = i;
    }
    return ret;
}

int maximalRectangle(char** matrix, int row, int col){
    if(row==0||col==0)return 0;
    int ret = 0, tmp;
    for(int i = 0; i < col; i++)
        sum[i]  = matrix[0][i] - '0';
    ret = largestRectangleArea(sum,col);
    for(int r = 1; r < row; r++)
    {
        for(int c = 0; c < col; c++)
            if(matrix[r][c] == '1')
                sum[c] += 1;
            else 
                sum[c] = 0;
        tmp = largestRectangleArea(sum,col);
        if(tmp > ret)
            ret = tmp;
    }
    return ret;
}

