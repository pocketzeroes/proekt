char*reformatDate(char*date){
  int i;
  char*sub0 = strdup(date);
  for(i=0; sub0[i]; i++){
    if(sub0[i]==' '){
      sub0[i]='\0';
      break;
    }
  }
  i++;
  char*sub1 = strdup(date+i);

  for(i=0; sub1[i]; i++){
    if(sub1[i]==' '){
      sub1[i]='\0';
      break;
    }
  }
  i++;
  char*sub2 = strdup(sub1+i);

  char fmt[100];
  strcpy(fmt, "");
  strcat(fmt, sub2);
  strcat(fmt, "-");

  if(     strcmp(sub1, "Jan")==0) strcat(fmt, "01");
  else if(strcmp(sub1, "Feb")==0) strcat(fmt, "02");
  else if(strcmp(sub1, "Mar")==0) strcat(fmt, "03");
  else if(strcmp(sub1, "Apr")==0) strcat(fmt, "04");
  else if(strcmp(sub1, "May")==0) strcat(fmt, "05");
  else if(strcmp(sub1, "Jun")==0) strcat(fmt, "06");
  else if(strcmp(sub1, "Jul")==0) strcat(fmt, "07");
  else if(strcmp(sub1, "Aug")==0) strcat(fmt, "08");
  else if(strcmp(sub1, "Sep")==0) strcat(fmt, "09");
  else if(strcmp(sub1, "Oct")==0) strcat(fmt, "10");
  else if(strcmp(sub1, "Nov")==0) strcat(fmt, "11");
  else if(strcmp(sub1, "Dec")==0) strcat(fmt, "12");

  strcat(fmt, "-");

  if(     strcmp(sub0, "1st" )==0) strcat(fmt, "01");
  else if(strcmp(sub0, "2nd" )==0) strcat(fmt, "02");
  else if(strcmp(sub0, "3rd" )==0) strcat(fmt, "03");
  else if(strcmp(sub0, "4th" )==0) strcat(fmt, "04");
  else if(strcmp(sub0, "5th" )==0) strcat(fmt, "05");
  else if(strcmp(sub0, "6th" )==0) strcat(fmt, "06");
  else if(strcmp(sub0, "7th" )==0) strcat(fmt, "07");
  else if(strcmp(sub0, "8th" )==0) strcat(fmt, "08");
  else if(strcmp(sub0, "9th" )==0) strcat(fmt, "09");
  else if(strcmp(sub0, "10th")==0) strcat(fmt, "10");
  else if(strcmp(sub0, "11th")==0) strcat(fmt, "11");
  else if(strcmp(sub0, "12th")==0) strcat(fmt, "12");
  else if(strcmp(sub0, "13th")==0) strcat(fmt, "13");
  else if(strcmp(sub0, "14th")==0) strcat(fmt, "14");
  else if(strcmp(sub0, "15th")==0) strcat(fmt, "15");
  else if(strcmp(sub0, "16th")==0) strcat(fmt, "16");
  else if(strcmp(sub0, "17th")==0) strcat(fmt, "17");
  else if(strcmp(sub0, "18th")==0) strcat(fmt, "18");
  else if(strcmp(sub0, "19th")==0) strcat(fmt, "19");
  else if(strcmp(sub0, "20th")==0) strcat(fmt, "20");
  else if(strcmp(sub0, "21st")==0) strcat(fmt, "21");
  else if(strcmp(sub0, "22nd")==0) strcat(fmt, "22");
  else if(strcmp(sub0, "23rd")==0) strcat(fmt, "23");
  else if(strcmp(sub0, "24th")==0) strcat(fmt, "24");
  else if(strcmp(sub0, "25th")==0) strcat(fmt, "25");
  else if(strcmp(sub0, "26th")==0) strcat(fmt, "26");
  else if(strcmp(sub0, "27th")==0) strcat(fmt, "27");
  else if(strcmp(sub0, "28th")==0) strcat(fmt, "28");
  else if(strcmp(sub0, "29th")==0) strcat(fmt, "29");
  else if(strcmp(sub0, "30th")==0) strcat(fmt, "30");
  else if(strcmp(sub0, "31st")==0) strcat(fmt, "31");

  return strdup(fmt);
}
