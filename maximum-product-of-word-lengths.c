#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int compareLength(const void *a, const void *b) {
  int len1 = strlen(*(char **) a);
  int len2 = strlen(*(char **) b);
  return (len1 > len2) - (len1 < len2);
}
void sortWordsByLength(char **words, int wordsSize) {
  qsort(words, wordsSize, sizeof(char *), compareLength);
}
void markLetters(char *word, int map[]) {
  memset(map, 0, sizeof(int)*26);
  for (; *word; word++)
    map[*word - 'a'] = 1;
}
int containLetters(char *word, int map[]) {
  for (; *word; word++)
    if (map[*word - 'a'])
      return 1;
  return 0;
}
int shareCommonLetter(char *word1, char *word2) {
  int letterMap[26];
  markLetters(word1, letterMap);
  return containLetters(word2, letterMap);
}
int maxProduct(char** words, int wordsSize) {
  int max = 0;
  int lo = 0;
  int hi = wordsSize - 1;
  int i;
  int len1, len2;
  qsort(words, wordsSize, sizeof(char *), compareLength);
  for (; hi >= lo; hi--) {
    for (i = hi - 1; i >= lo; i--) {
      if (!shareCommonLetter(words[hi], words[i])) {
        len1 = strlen(words[hi]);
        len2 = strlen(words[i]);
        if (len1 * len2 >= max) {
          max = len1 * len2;
          lo = i;
        }
      }
    }
  }
  return max;
}
int main(int argc, char *argv[]){
  char *words[] = {"a", "aa", "aaa", "aaaa"};
  int len = 4;
  printf("%d\n", maxProduct((char **) words, len));
  return 0;
}



























