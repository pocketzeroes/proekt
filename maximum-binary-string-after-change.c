char*maximumBinaryString(char*binary){
    int binary_size=strlen(binary);
    int x = 0;
    while(x < binary_size && binary[x] == '1')
      x += 1;
    if(x == binary_size)
      return binary;
    int s = 0;
    for(int i = x + 1; i < binary_size; i += 1)
      s += binary[i] == '1';
    for(int i = 0; i < binary_size; i += 1)
      binary[i] = '1';
    binary[binary_size - s - 1] = '0';
    return binary;
}
