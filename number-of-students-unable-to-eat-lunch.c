int countStudents(int*students, int studentsSz, int*sandwiches, int sandwichesSz){
    int one = 0, zero = 0;
    for(int z=0;z<studentsSz;z++){int x = students[z];
        if(x==1) 
          one++;
        else 
          zero++;
    }
    for(int z=0;z<sandwichesSz;z++){int x = sandwiches[z];
        if(x==1){
            if(one==0) 
              break;
            one--;
        } 
        else{
            if(zero==0) 
              break;
            zero--;
        }
    }
    return one+zero;
}
