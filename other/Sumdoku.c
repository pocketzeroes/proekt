#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>
typedef unsigned short WORD;
typedef unsigned char BYTE;
char inbuf[256];


int constraints[15][9];
WORD valid_masks[10] = {0, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x100};
#define ALL_MASK  0x1ff

typedef struct _search_state_
{
  WORD avail_mask[9][9];  
  BYTE row_avail_counts[9][9]; 
  BYTE col_avail_counts[9][9]; 
  BYTE box_avail_counts[3][3][9]; 
  BYTE val_set[9][9]; 
} SEARCH_STATE;
SEARCH_STATE states[81];

void search_init()
{
  SEARCH_STATE *pss = &(states[0]);
  int i, j, k;
  for(i = 0; i < 9; i++) {
    for(j = 0; j < 9 ; j++) {
      pss->avail_mask[i][j] = ALL_MASK;
      pss->val_set[i][j] = 0;
      pss->row_avail_counts[i][j] = 9;
      pss->col_avail_counts[i][j] = 9;
    }
  }
  for(i = 0; i < 3; i++) {
    for(j = 0; j < 3 ; j++) {
      for(k = 0; k < 9 ; k++){
        pss->box_avail_counts[i][j][k] = 9;
      }
    }
  }
}

int scan_convert(int *prow, int n, const char *s)
{
  int i;
  for(i = 0; i < n; i++, s++){
    switch(*s){
    case '<': *prow++ = -1; break;
    case '=': *prow++ = 0; break;
    case '>': *prow++ = 1; break;
    default: return(i);
    }
  }
  return(i);
}

int scan_constraints()
{
  int i, j, n;
  for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
      if(fgets(&(inbuf[0]), 255, stdin) == NULL)
      {
        fprintf(stderr, "Read of first line of region %d block %d failed\n", j, i);
        return -21;
      }
      n = scan_convert(&(constraints[5*i+2*j][0]), 6, &(inbuf[0]));
      if(n != 6){
        fprintf(stderr, "Scan of first line of region %d block %d failed got %d wanted 6: %s", j, i, n, &(inbuf[0]));
        return(-22);
      }
      if(j < 2) {
        if(fgets(&(inbuf[0]), 255, stdin) == NULL)
        {
          fprintf(stderr, "Read of second line of region %d block %d failed\n", j, i);
          return -23;
        }
        n = scan_convert(&(constraints[5*i+2*j+1][0]), 9, &(inbuf[0]));
        if(n != 9) {
          fprintf(stderr, "Scan of second line of region %d block %d failed got %d wanted 9: %s\n", j, i, n, &(inbuf[0]));
          return -24;
        }
      }
    }
  }
  return 0;
}

WORD checkEqual(WORD baseMask, WORD chkMask)
{
  WORD result = 0;
  int i;
  if(valid_masks[5] & baseMask) {
    result |= valid_masks[5];
  }
  for(i = 1; i <= 9 ; i++) {
    if(((valid_masks[i] & chkMask) == 0) && (valid_masks[10-i] & baseMask)) {
      result |= valid_masks[10-i];
    }
  }
  return result;
}

WORD checkLess(WORD baseMask, WORD chkMask)
{
  WORD result = 0;
  int i;
  if(valid_masks[9] & baseMask) {
    result |= valid_masks[9];
  }
  for(i = 1; i <= 8 ; i++) {
    if((valid_masks[i] & chkMask) != 0) {
      break;
    } else if(valid_masks[9-i] & baseMask) {
      result |= valid_masks[9-i];
    }
  }
  return result;
}

WORD checkGreater(WORD baseMask, WORD chkMask)
{
  WORD result = 0;
  int i;
  if(valid_masks[1] & baseMask) {
    result |= valid_masks[1];
  }
  for(i = 9; i >= 3 ; i--) {
    if((valid_masks[i] & chkMask) != 0) {
      break;
    } else if(valid_masks[11-i] & baseMask) {
      result |= valid_masks[11-i];
    }
  }
  return result;
}

WORD checkConstraint(int constraint, WORD baseMask, WORD chkMask)
{
  if(constraint < 0) {
    return checkLess(baseMask, chkMask);
  } else if(constraint > 0) {
    return checkGreater(baseMask, chkMask);
  } else {
    return checkEqual(baseMask, chkMask);
  }
}

int check_constraints(SEARCH_STATE *pss)
{
  int i, row, col, baseConsRow, baseConsCol, scan_count, change_count = 1;
  WORD baseMask, chkMask, resultMask, totResult;
  scan_count = 0;
  while(change_count > 0) {
    scan_count++;
    change_count = 0;
    for(row = 0, baseConsRow = 0; row < 9 ; row++) {
      for(col = 0, baseConsCol = 0; col < 9 ; col++) {
        if(pss->val_set[row][col] == 0) { 
          baseMask = pss->avail_mask[row][col];
          totResult = 0;  
          if((col %3) != 0) { 
            chkMask = pss->avail_mask[row][col-1];
            resultMask = checkConstraint(constraints[baseConsRow][baseConsCol-1], baseMask, chkMask);
            if(resultMask != 0) {
              baseMask &= ~resultMask;
              change_count++;
              totResult |= resultMask;
            }
          }
          if((col %3) != 2) { 
            chkMask = pss->avail_mask[row][col+1];
            resultMask = checkConstraint(constraints[baseConsRow][baseConsCol], baseMask, chkMask);
            if(resultMask != 0) {
              baseMask &= ~resultMask;
              change_count++;
              totResult |= resultMask;
            }
          }
          if((row %3) != 0) { 
            chkMask = pss->avail_mask[row-1][col];
            resultMask = checkConstraint(constraints[baseConsRow-1][col], baseMask, chkMask);
            if(resultMask != 0) {
              baseMask &= ~resultMask;
              change_count++;
              totResult |= resultMask;
            }
          }
          if((row %3) != 2) { 
            chkMask = pss->avail_mask[row+1][col];
            resultMask = checkConstraint(constraints[baseConsRow+1][col], baseMask, chkMask);
            if(resultMask != 0) {
              baseMask &= ~resultMask;
              change_count++;
              totResult |= resultMask;
            }
          }
          if(baseMask == 0) { 
            return -1;
          }
          pss->avail_mask[row][col] = baseMask;
          if(totResult != 0) { 
            for(i = 0; i < 9 ; i++) {
              if(valid_masks[i] & totResult) {
                pss->col_avail_counts[col][i-1]--;
                pss->row_avail_counts[row][i-1]--;
                pss->box_avail_counts[row/3][col/3][i-1]--;
              }
            }
          }
        }
        if((col %3) != 2) { 
          baseConsCol++;
        }
      }
      if((row % 3) != 2) {  
        baseConsRow += 2;
      } else {
        baseConsRow++;
      }
    }
  }
  return 0;
}

#define STYP_ROW  1 
#define STYP_COL  2 
#define STYP_BOX  3 
typedef struct _solve_data_ {
  int solve_type;
  int solve_val;
  int solve_row;
  int solve_col;
  int solve_cnt;
  int solve_index;
  int test_row;
  int test_col;
} SOLVE_DATA;

int GetSolveStep(SEARCH_STATE *pss, SOLVE_DATA *psd)
{
  int i, j, k;
  psd->solve_cnt = 10;
  for(i = 0; i < 9; i++) {
    for(j = 0; j < 9; j++) {
      if(pss->row_avail_counts[i][j] < psd->solve_cnt) {
        psd->solve_cnt = pss->row_avail_counts[i][j];
        psd->solve_type = STYP_ROW;
        psd->solve_row = i;
        psd->solve_val = j+1;
      }
    }
  }
  for(i = 0; i < 9; i++) {
    for(j = 0; j < 9; j++) {
      if(pss->col_avail_counts[i][j] < psd->solve_cnt) {
        psd->solve_cnt = pss->col_avail_counts[i][j];
        psd->solve_type = STYP_COL;
        psd->solve_col = i;
        psd->solve_val = j+1;
      }
    }
  }
  for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
      for(k = 0; k < 9 ; k++) {
        if(pss->box_avail_counts[i][j][k] < psd->solve_cnt) {
          psd->solve_cnt = pss->box_avail_counts[i][j][k];
          psd->solve_type = STYP_BOX;
          psd->solve_row = i;
          psd->solve_col = j;
          psd->solve_val = k+1;
        }
      }
    }
  }
  if(psd->solve_cnt == 0) { 
    return -1;
  } else {
    return 0;
  }
}

int FindNextTest(SEARCH_STATE *pss, SOLVE_DATA *psd)
{
  int i, j, starti, startj;
  WORD mask = valid_masks[psd->solve_val];
  if(psd->solve_index >= psd->solve_cnt) {
    return -1;
  }
  switch(psd->solve_type) {
  case STYP_ROW:
    if(psd->solve_index == 0) {
      startj = 0;
    } else {
      startj = psd->test_col+1;
    }
    i = psd->solve_row;
    for(j = startj ; j < 9 ; j++) {
      if(pss->avail_mask[i][j] & mask) {
        psd->test_col = j;
        psd->test_row = i;
        psd->solve_index++;
        return 0;
      }
    }
    return -1;
  case STYP_COL:
    if(psd->solve_index == 0) {
      starti = 0;
    } else {
      starti = psd->test_row+1;
    }
    j = psd->solve_col;
    for(i = starti ; i < 9 ; i++) {
      if(pss->avail_mask[i][j] & mask) {
        psd->test_col = j;
        psd->test_row = i;
        psd->solve_index++;
        return 0;
      }
    }
    return -1;
  case STYP_BOX:
    if(psd->solve_index == 0) {
      starti = 0;
      startj = 0;
    } else {
      starti = psd->test_row - 3*psd->solve_row;
      startj = psd->test_col+1 - 3*psd->solve_col;
    }
    for(i = starti; i < 3 ; i++) {
      for(j = startj ; j < 3; j++) {
        if(pss->avail_mask[i + 3*psd->solve_row][j + 3*psd->solve_col] & mask) {
          psd->test_col = j + 3*psd->solve_col;
          psd->test_row = i + 3*psd->solve_row;
          psd->solve_index++;
          return 0;
        }
      }
    }
    return -1;
  default:
    fprintf(stderr, "bad solve type %d\n", psd->solve_type);
    return -1;
  }
}

int ApplyChoice(SEARCH_STATE *pss, int row, int col, int val)
{
  int i, j, boxr, boxc;
  WORD mask = valid_masks[val];
  if(pss->val_set[row][col] != 0) {
    fprintf(stderr, "ApplyChoice: row %d col %d val %d already set to %d\n", row, col, val, pss->val_set[row][col]);
    return -1;
  }
  pss->val_set[row][col] = val;
  boxr = row/3;
  boxc = col/3;
  for(j = 0; j < 9 ; j++) {
    if(pss->avail_mask[row][j] & mask) { 
      pss->box_avail_counts[boxr][j/3][val-1]--;
      pss->col_avail_counts[j][val-1]--;
    }
    pss->avail_mask[row][j] &= ~mask;
  }
  for(i = 0; i < 9 ; i++) {
    if(pss->avail_mask[i][col] & mask) {
      pss->box_avail_counts[i/3][boxc][val-1]--;
      pss->row_avail_counts[i][val-1]--;
    }
    pss->avail_mask[i][col] &= ~mask;
  }
  boxr = row/3;
  boxc = col/3;
  for(i = 3*boxr; i < 3*(boxr+1); i++) {
    for(j = 3*boxc; j < 3*(boxc+1); j++) {
      if(pss->avail_mask[i][j] & mask) {
        pss->col_avail_counts[j][val-1]--;
        pss->row_avail_counts[i][val-1]--;
      }
      pss->avail_mask[i][j] &= ~mask;
    }
  }
  for(i = 1; i <= 9 ; i++) {
    if((i != val) && ((pss->avail_mask[row][col] & valid_masks[i]) != 0)){
      pss->box_avail_counts[row/3][col/3][i-1]--;
      pss->col_avail_counts[col][i-1]--;
      pss->row_avail_counts[row][i-1]--;
    }
  }
  pss->avail_mask[row][col] = mask; 
  pss->row_avail_counts[row][val-1] = 32; 
  pss->col_avail_counts[col][val-1] = 32; 
  pss->box_avail_counts[boxr][boxc][val-1]= 32; 
  return 0;
}

int Solve(int level)
{
  SEARCH_STATE *pssnxt, *pss = &(states[level]);
  SOLVE_DATA sd;
  int i, j;
  if(GetSolveStep(pss, &sd) != 0) { 
    return -1;
  }
#ifdef DEBUG
  printf("level %d solve type %d row %d col %d val %d cnt %d\n", level,
    sd.solve_type, sd.solve_row, sd.solve_col, sd.solve_val, sd.solve_cnt);
#endif
  sd.solve_index = 0;
  while(FindNextTest(pss, &sd) == 0) {  
    if(level == 80) { 
      pss->val_set[sd.test_row][sd.test_col] = sd.solve_val;
      return 0;
    } else {  
      pssnxt = &(states[level+1]);
      *pssnxt = *pss;
#ifdef DEBUG
      fprintf(stderr, "try row %d col %d val %d\n", sd.test_row, sd.test_col, sd.solve_val);
#endif
      if(ApplyChoice(pssnxt, sd.test_row, sd.test_col, sd.solve_val) == 0) { 
#ifdef DEBUG
        check_soln(pssnxt);
#endif
        if(check_constraints(pssnxt) == 0) {  
#ifdef DEBUG
          check_soln(pssnxt);
#endif
          if(Solve(level+1) == 0) { 
            for(i = 0; i < 9; i++) {
              for(j = 0; j < 9 ; j++) {
                pss->val_set[i][j] = pssnxt->val_set[i][j];
              }
            }
            return 0;
          }
        }
#ifdef DEBUG
      } else {
        fprintf(stderr, "Apply Choice failed at level %d \n", level);
#endif
      }
    }
  }
  return -1;
}
int main()
{
  int nprob=1, curprob, index=1, ret, i, j;

  for(curprob = 1; curprob <= nprob ; curprob++)
  {
    search_init();
    if((ret = scan_constraints()) != 0) {
      return ret;
    }
    if(check_constraints(&(states[0])) != 0) { 
      fprintf(stderr, "problem index %d init check constraints failed\n",
        index);
      return -8;
    }
#ifdef DEBUG
    if(check_soln(&(states[0])) != 0) {
      fprintf(stderr, "problem index %d after init check constraints no match\n",
        index);
      return -18;
    }
#endif
    if(Solve(0) != 0) { 
      fprintf(stderr, "problem index %d no solution\n",
        index);
      return -9;
    }
    for(i = 0; i < 9 ; i++) {
      for(j = 0; j < 9 ; j++) {
        printf("%d ", states[0].val_set[i][j]);
      }
      printf("\n");
    }
  }
  return 0;
}

