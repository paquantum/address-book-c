#pragma once

typedef struct USERDATA
{
    char name[32];
    char address[128];
    char phone[32];
    char active[5];
    struct USERDATA* pPrev;
    struct USERDATA* pNext;
} USERDATA;

USERDATA g_HeadNode;
USERDATA g_TailNode;

USERDATA* SearchByName(const char* pszName);
USERDATA** SearchByNames(const char* pszName);
USERDATA* SearchByPhone(const char* pszPhone, int* pIdx);
USERDATA* SearchByNameAndPhone(const char* pszName, const char* pszPhone, int* fpPos);
void SaveToFile(const char* pszName, const char* pszAddress, const char* pszPhone, const char* pszActive);
void UpdateToFile(const char* pszName, const char* pszAddress, const char* pszPhone, const char* pszActive, USERDATA* pTmp, int fpPos);
USERDATA* SearchToRemove(const char* pszPhone, int* fpPos);
void RemoveFromFile(USERDATA* pTmp, int fpPos);
int ValidationPhone(const char* pszPhone);
void AddNewNode(const char* pszName, const char* pszAddress, const char* pszPhone, const char* pszActive);
void InitList();
void ReleaseList();
int IsEmpty();
void RemoveNode(USERDATA* pPrev);