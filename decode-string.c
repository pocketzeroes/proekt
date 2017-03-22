struct StringNode {
	int cnt;
	int len;
	char *pCurStr;
	struct StringNode *pChildNxt;
	struct StringNode *pSubStrNxt;
};
int CntToSubStrEnd(char *s) {
	int RetVal = 0;
	while (*s && ((*s < '0') || (*s > '9')) && (*s != '[') && (*s != ']')) {
		s++;
		RetVal++;
	}
	return RetVal;
}
int GetNum(char *s, int *pNum) {
	int RetVal = 0;
	*pNum = 0;
	while (*s && (*s >= '0') && (*s <= '9')) {
		*pNum = *pNum * 10;
		*pNum = *pNum + *s - '0';
		RetVal++;
		s++;
	}
	return RetVal;
}
int CntSymboInterval(char *s) {
	int Flag = 1;
	int RetVal = 0;
	while (*s != '[') s++;
	s++;
	while (*s && Flag) {
		if (*s == '[')
			Flag++;
		else if (*s == ']')
			Flag--;
		RetVal++;
		s++;
	}
	RetVal--;
	return RetVal;
}
int StringProc(char *s, int len, struct StringNode **pNode) {
	int i;
	int CurStrLen = 0;
	int AccumStrLen = 0;
	int ProcLen = 0;
	struct StringNode *pCurNode;
	pCurNode = (struct StringNode *)calloc(1, sizeof(struct StringNode));
	*pNode = pCurNode;
	while (ProcLen < len) {
		if ((*s >= '0') && (*s <= '9')) {
			CurStrLen = GetNum(s, &(pCurNode->cnt));
			s += CurStrLen;
			ProcLen += CurStrLen;
			CurStrLen = CntSymboInterval(s);
			pCurNode->len = StringProc(s + 1
				, CurStrLen
				, &(pCurNode->pChildNxt));
			s = s + 2 + CurStrLen;
			AccumStrLen += ((pCurNode->len) * (pCurNode->cnt));
			ProcLen += (CurStrLen + 2);
		}
		else {
			CurStrLen = CntToSubStrEnd(s);
			pCurNode->cnt = 1;
			pCurNode->len = CurStrLen;
			pCurNode->pCurStr = (char *)malloc((CurStrLen + 1) * sizeof(char));
			for (i = 0; i < CurStrLen; i++) {
				*(pCurNode->pCurStr + i) = *(s + i);
			}
			*(pCurNode->pCurStr + i) = 0;
			s += CurStrLen;
			AccumStrLen += CurStrLen;
			ProcLen += CurStrLen;
		}
		if (ProcLen < len) {
			pCurNode->pSubStrNxt
				= (struct StringNode *)calloc(1, sizeof(struct StringNode));
			pCurNode = pCurNode->pSubStrNxt;
		}
	}
	return AccumStrLen;
}
void FillInStr(struct StringNode *pHead, char *pDst) {
	int i, j;
	struct StringNode *pSubN;
	while (pHead) {
		for (i = 0; i < pHead->cnt; i++) {
			if (pHead->pCurStr) {
				for (j = 0; j < pHead->len; j++) {
					*(pDst + j) = *(pHead->pCurStr + j);
				}
				pDst = pDst + pHead->len;
			}
			else {
				pSubN = pHead->pChildNxt;
				FillInStr(pSubN, pDst);
				pDst = pDst + pHead->len;
			}
		}
		pHead = pHead->pSubStrNxt;
	}
}
char* decodeString(char* s) {
	char *pRet;
	int len = strlen(s);
	struct StringNode *pHead = NULL;
	if (len == 0) {
	    pRet = (char *)malloc(sizeof(char));
	    *pRet = 0;
	    return pRet;	    
	}
	len = StringProc(s, len, &pHead);
	pRet = (char *)malloc((len + 1) * sizeof(char));
	FillInStr(pHead, pRet);
	*(pRet + len) = 0;
	return pRet;
}















