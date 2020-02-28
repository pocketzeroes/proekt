#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

enum charclass {NEITHER = 0, CONSONANT = 1, VOWEL = 2};

int delimiter, i, line1, line2, total, wordcount;
char *iostatus, *result, *token;
int syllablecount[20];
char *word[20];
char lineimage[204], originalline[204];
enum charclass lettertype[204];

void abend (char *message){
  (void) fputs (message, stderr);
  (void) fputc ('\n', stderr);
  exit (4);
}
enum charclass chartype (int thischar){
   static const enum charclass letter[26] =
   {VOWEL, CONSONANT, CONSONANT, CONSONANT, VOWEL, CONSONANT, CONSONANT, CONSONANT, VOWEL, CONSONANT, CONSONANT, CONSONANT, CONSONANT,
   CONSONANT, VOWEL, CONSONANT, CONSONANT, CONSONANT, CONSONANT, CONSONANT, VOWEL, CONSONANT, CONSONANT, CONSONANT, VOWEL, CONSONANT};
   int offset;
   enum charclass result;
   offset = (toupper (thischar)) - 'A';
   result = ((offset < 0)  ||  (offset > 25)) ? NEITHER : letter[offset];
   return (result);
}
int numsyllables (char *word){
   int i, nextchar, testchar, wordlen;
   int count = 0;
   enum charclass state, thisclass;
   struct{
      int lastchar;
      enum charclass lasttype;
   } lastletter[4];
   wordlen = (int) strlen (word);
   state = NEITHER;
   for (i = 0; i < 4; i++){
      lastletter[i].lastchar = 0;
      lastletter[i].lasttype = NEITHER;
   }
   for (i = 0; i < wordlen; i++){
      testchar = toupper ((int) word[i]);
      if ((chartype (testchar)) == NEITHER)
         break;
      if (testchar == 'Q'){
         thisclass = CONSONANT;
         nextchar = toupper ((int) word[(i + 1)]);
         if (nextchar == 'U')
            i++;
      }
      else if (testchar == 'Y'){
         thisclass = VOWEL;
         nextchar = toupper ((int) word[(i + 1)]);
         if ((isupper (nextchar))  &&  (nextchar != 'Y')  && ((chartype (nextchar)) == VOWEL))
            thisclass = CONSONANT;
      }
      else
         thisclass = chartype (testchar);
      lastletter[3] = lastletter[2];
      lastletter[2] = lastletter[1];
      lastletter[1] = lastletter[0];
      lastletter[0].lastchar = testchar;
      lastletter[0].lasttype = thisclass;
      if (thisclass == VOWEL){
         if (state != VOWEL){
            if (testchar == 'E'){
               if ((chartype (toupper (word[(i + 1)]))) == NEITHER){
                  if ((lastletter[1].lastchar == 'L')  && (lastletter[2].lasttype == CONSONANT))
                     count++;
               }
               else if ((toupper ((int) word[(i + 1)]) == 'S')  && ((chartype (toupper ((int) word[(i + 2)]))) == NEITHER)){
                  if ((lastletter[1].lasttype == CONSONANT)  && (lastletter[2].lasttype == CONSONANT))
                     count++;
               }
               else
                  count++;
            }
            else
               count++;
            state = VOWEL;
         }
      }
      else
         state = CONSONANT;
   }
   if(!count)
      count = 1;
   return (count);
}
int main(){
   while (fgets (lineimage, 202, stdin) != NULL){
      wordcount = 0;
      for (i = 0; i < 20; i++)
         syllablecount[i] = 0;
      (void) strncpy (originalline, lineimage, 203);
      token = strtok (lineimage, " \t\n");
      while ((wordcount < 20)  &&  (token != NULL)){
         word[wordcount] = token;
         syllablecount[wordcount++] = numsyllables (token);
         token = strtok (NULL, " \t\n");
      }
      line1 = line2 = total = 0;
      for (i = 0; i < 20; i++){
         total += syllablecount[i];
         if (total == 5)
            line1 = 1;
         else if (total == 12)
            line2 = 1;
      }
      if ((total == 17)  &&  line1  &&  line2){
         total = 0;
         for (i = 0; syllablecount[i]; i++){
            (void) fputs (word[i], stdout);
            total += syllablecount[i];
            delimiter = ((total == 5)  ||  (total == 12)  || (total == 17)) ? '\n' : ' ';
            (void) fputc (delimiter, stdout);
         }
      }
      else
         fputs (originalline, stdout);
   }
   return 0;
}
