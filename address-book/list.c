#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "list.h"
#include "fileIO.h"

USERDATA g_HeadNode = { "__Dummy Head__" };
USERDATA g_TailNode = { "__Dummy Tail__" };

USERDATA* SearchByName(const char* pszName) {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb");
	if (fp == NULL) {
		puts("ERROR: Not Found File");
		return NULL;
	}

	USERDATA* pTmp = g_HeadNode.pNext;
	while (pTmp != NULL) {
		if (strcmp(pTmp->name, pszName) == 0) {
			return pTmp;
		}

		pTmp = pTmp->pNext;
	}
	fclose(fp);
	return NULL;
}

// Search 부분, 이름은 중복 가능이라 여러 값 받기
USERDATA** SearchByNames(const char* pszName) {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb");
	if (fp == NULL) {
		puts("ERROR: Not Found File");
		return NULL;
	}
	ReleaseList();

	USERDATA* userLists = NULL;
	USERDATA user = { 0 };	
	int cnt = 0;
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0) {
		if (strcmp(user.name, pszName) == 0) {
			AddNewNode(user.name, user.address, user.phone, user.active);
			cnt++;
		}
		memset(&user, 0, sizeof(user));
	}

	fclose(fp);

	USERDATA** aList = malloc(sizeof(USERDATA*) * cnt);
	memset(aList, 0, sizeof(USERDATA*) * cnt);
	USERDATA* pTmp = g_HeadNode.pNext;
	for (int i = 0; i < cnt; i++) {
		aList[i] = pTmp;
		pTmp->pNext;
	}
	
	if (cnt > 0) return aList;
	else return NULL;
}

USERDATA* SearchByPhone(const char* pszPhone, int* fpPos) {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb");
	if (fp == NULL) {
		puts("ERROR: Not Found File to SearchByPhone");
		return NULL;
	}

	USERDATA user = { 0 };
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0) {
		if (fpPos != NULL) (*fpPos)++;
		if (strncmp(pszPhone, user.phone, strlen(pszPhone)) == 0) {
			AddNewNode(user.name, user.address, user.phone, user.active);
			USERDATA* pTmp = g_HeadNode.pNext;
			while (pTmp != NULL) {
				if (strncmp(pTmp->phone, pszPhone, strlen(pszPhone)) == 0) {
					fclose(fp);
					return pTmp;
				}
				pTmp = pTmp->pNext;
			}
		}
	}

	fclose(fp);

	return NULL;
}

USERDATA* SearchByNameAndPhone(const char* pszName, const char* pszPhone, int* fpPos) {
	USERDATA* pTmp = SearchByPhone(pszPhone, fpPos);
	if (pTmp == NULL) return NULL;
	if (strcmp(pTmp->name, pszName) == 0) return pTmp;
	return NULL;
}

void SaveToFile(const char* pszName, const char* pszAddress, const char* pszPhone, const char* pszActive) {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info2.dat", "ab");
	if (fp == NULL) {
		puts("ERROR: Not Found File to SaveToFile");
		return;
	}
	
	fseek(fp, 0, SEEK_END);
	USERDATA user = { 0 };
	strcpy_s(user.name, sizeof(user.name), pszName);
	strcpy_s(user.address, sizeof(user.address), pszAddress);
	strcpy_s(user.phone, sizeof(user.phone), pszPhone);
	strcpy_s(user.active, sizeof(user.active), pszActive);
	fwrite(&user, sizeof(USERDATA), 1, fp);

	fclose(fp);
}

void UpdateToFile(const char* pszName, const char* pszAddress, const char* pszPhone, const char* pszActive, USERDATA* pTmp, int fpPos) {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb+");
	if (fp == NULL) {
		puts("ERROR: Not Found File to UpdateToFile");
		return;
	}
	printf("fpPos: %d\n", fpPos);
	fseek(fp, sizeof(USERDATA) * fpPos, SEEK_SET);
	USERDATA user = { 0 };
	strcpy_s(user.name, sizeof(user.name), pszName);
	strcpy_s(user.address, sizeof(user.address), pszAddress);
	strcpy_s(user.phone, sizeof(user.phone), pszPhone);
	strcpy_s(user.active, sizeof(user.active), pszActive);
	fwrite(&user, sizeof(USERDATA), 1, fp);

	printf("기존 정보: 이름, 주소, 전화번호에서\n");
	printf("%s, %s, %s, %s\n", pTmp->name, pTmp->address, pTmp->phone, pTmp->active);
	printf("변경 정보: 이름, 주소, 전화번호로 변경됐습니다.\n");
	printf("%s, %s, %s, %s\n", pszName, pszAddress, pszPhone, pszActive);

	ReleaseList();
	
	fclose(fp);
	AddNewNode(pszName, pszAddress, pszPhone, pszActive);
}

USERDATA* SearchToRemove(const char* pszPhone, int *fpPos) {
	
	USERDATA* pTmp = SearchByPhone(pszPhone, fpPos);
	if (pTmp == NULL) return NULL;
	return pTmp;
}

void RemoveFromFile(USERDATA* pTmp, int fpPos) {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb+");
	if (fp == NULL) {
		puts("ERROR: Not Found File to RemoveFromFile");
		return;
	}
	fseek(fp, sizeof(USERDATA) * fpPos, SEEK_SET);
	USERDATA user = { 0 };
	strcpy_s(user.name, sizeof(user.name), pTmp->name);
	strcpy_s(user.address, sizeof(user.address), pTmp->address);
	strcpy_s(user.phone, sizeof(user.phone), pTmp->phone);
	strcpy_s(user.active, sizeof(user.active), pTmp->active);
	fwrite(&user, sizeof(USERDATA), 1, fp);

	fclose(fp);
	ReleaseList();
	AddNewNode(user.name, user.address, user.phone, user.active);
	printf("%s, %s, %s, %s 사용자의 정보가 삭제됐습니다.\n", user.name, user.address, user.phone, user.active);
}

int ValidationPhone(const char* pszPhone) {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb");
	if (fp == NULL) {
		puts("ERROR: Not Found File to SearchByPhone");
		return NULL;
	}

	USERDATA user = { 0 };
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0) {
		if (strncmp(pszPhone, user.phone, strlen(pszPhone)) == 0) {
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);

	return 0;
}

void AddNewNode(const char* pszName, const char* pszAddress, const char* pszPhone, const char* pszActive) {
	USERDATA* pNewNode = (USERDATA*)malloc(sizeof(USERDATA));
	strcpy_s(pNewNode->name, sizeof(pNewNode->name), pszName);
	strcpy_s(pNewNode->address, sizeof(pNewNode->address), pszAddress);
	strcpy_s(pNewNode->phone, sizeof(pNewNode->phone), pszPhone);
	strcpy_s(pNewNode->active, sizeof(pNewNode->active), pszActive);
	pNewNode->pPrev = NULL;
	pNewNode->pNext = NULL;

	USERDATA* pPrevNode = g_TailNode.pPrev;
	pNewNode->pPrev = g_TailNode.pPrev;
	pNewNode->pNext = &g_TailNode;

	pPrevNode->pNext = pNewNode;
	g_TailNode.pPrev = pNewNode;
}

void InitList() {
	g_HeadNode.pNext = &g_TailNode;
	g_TailNode.pPrev = &g_HeadNode;
}

void ReleaseList() {
	USERDATA* pTmp = g_HeadNode.pNext;
	USERDATA* pDelete;
	while (pTmp != NULL && pTmp != &g_TailNode) {
		pDelete = pTmp;
		pTmp = pTmp->pNext;
		free(pDelete);
	}
	InitList();
}

int IsEmpty() {
	if (g_HeadNode.pNext == &g_TailNode || g_HeadNode.pNext == NULL)
		return 1;
	return 0;
}

void RemoveNode(USERDATA* pRemove) {
	USERDATA* pPrev = pRemove->pPrev;
	USERDATA* pNext = pRemove->pNext;

	pPrev->pNext = pRemove->pNext;
	pNext->pPrev = pRemove->pPrev;

	free(pRemove);
}