#include<stdio.h>
#include<string.h>
static const int month_off[12] = {0,1,-1,0,0,1,1,2,3,3,4,4};
static int in_range[366];

static int is_leap (int y){
  if (y % 4)
    return 0;
  if (y % 100)
    return 1;
  return y % 400 == 0;
}
static int num_leap_since_1600 (int y){
  int n = y - 1600;
  return ((n + 3) / 4) - ((n + 99) / 100) + ((n + 399) / 400);
}
static int day_in_year (int d, int m, int y){
  int diy = 30 * (m - 1) + month_off[m - 1] + d - 1;
  if (is_leap (y) && m >= 3)
    diy++;
  return diy;
}
static int days_since_1600 (int d, int m, int y){
  return (y - 1600) * 365 + num_leap_since_1600 (y) + day_in_year (d, m, y);
}
static int day_in_week (int dse){
  return (dse + 5) % 7;
}
static int easter_monday (int y){
  int golden, solar, lunar, p, pse, dn;
  golden = (y % 19) + 1;
  solar = (y - 1600) / 100 - (y - 1600) / 400 ;
  lunar = (((y - 1400) / 100) * 8) / 25;
  p = (3003 - (11 * golden) + solar - lunar) % 30;
  if (p == 29 || (p == 28 && golden > 11))
    p--;
  pse = p + days_since_1600 (21, 3, y);
  dn = day_in_week (pse);
  if (dn == 6)
    return pse + 8;
  else
    return pse + 7 - day_in_week (pse);
}
static int parse_date (char *dm, int y, int int_start){
  int d, m;
  sscanf (dm, "%d.%d", &d, &m);
  if (!is_leap (y) && d == 29 && m == 2){
    if (int_start){
      d = 1;
      m = 3;
    }
    else
      d--;
  }
  return days_since_1600 (d, m, y);
}
static void mark_ranges (char *ranges, int y){
  int base = days_since_1600 (1, 1, y), cont = 1;
  memset (in_range, 0, sizeof (in_range));
  while (cont){
    char *act = ranges;
    char *end = strchr (ranges, ',');
    int from, to, i;
    if (end){
      ranges = end + 1;
      *end = 0;
    }
    else
      cont = 0;
    end = strchr (act, '-');
    if (end){
      *end++ = 0;
      from = parse_date (act, y, 1);
      to = parse_date (end, y, 0);
    }
    else{
      from = parse_date (act, y, 1);
      to = parse_date (act, y, 0);
    }
    for (i = from; i <= to; i++)
      in_range[i - base] = 1;
  }
}
static int is_holiday (int d, int y){
  int wday = day_in_week (d);
  if (wday == 6)
    return 1;
  if(d == days_since_1600 (1, 1, y)   ||
     d == days_since_1600 (1, 5, y)   ||
     d == days_since_1600 (8, 5, y)   ||
     d == days_since_1600 (5, 7, y)   ||
     d == days_since_1600 (6, 7, y)   ||
     d == days_since_1600 (28, 9, y)  ||
     d == days_since_1600 (28, 10, y) ||
     d == days_since_1600 (17, 11, y) ||
     d == days_since_1600 (24, 12, y) ||
     d == days_since_1600 (25, 12, y) ||
     d == days_since_1600 (26, 12, y))
     return 1;
  if(wday != 0)
    return 0;
  return d == easter_monday (y);
}
static int is_workday (int d, int y){
  int wday = day_in_week (d);
  if (wday > 4)
    return 0;
  return !is_holiday (d, y);
}
static int satisfies (char *restr, int d, int y){
  int wday = day_in_week (d);
  for (; *restr; restr++){
    if ('1' <= *restr && *restr <= '7'){
      if (wday + '1' == *restr)
        return 1;
      continue;
    }
    switch (*restr){
      case 't':
        if (is_holiday (d, y))
          return 1;
        break;
      case 'w':
        if (is_workday (d, y))
          return 1;
        break;
      case 'a':
        if (is_workday (d, y)
            && is_holiday (d - 1, y))
          return 1;
        break;
    }
  }
  return 0;
}
int main(){
  char restr[20], ranges[2000];
  int y, d;
  while (scanf ("%s %s %d", restr, ranges, &y) == 3){
    int base = days_since_1600 (1, 1, y), length = 365 + is_leap (y);
    int n = 0;
    mark_ranges (ranges, y);
    for (d = base; d < base + length; d++)
      if (in_range[d - base] && satisfies (restr, d, y))
        n++;
    printf ("%d\n", n);
  }
  return 0;
}
