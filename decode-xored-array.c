int*decode(int*encoded, int encodedSz, int first, int*rsz){
  int*ret=calloc(encodedSz+1, sizeof(int));
  ret[0]=first;
  for(int z=0;z<encodedSz;z++){int out=encoded[z];
    ret[z+1]=(first ^ out);
    first ^= out;
  }
 *rsz=encodedSz+1;
  return ret;
}
