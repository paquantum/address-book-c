#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include "list.h"
#include "ui.h"
#include "fileIO.h"

MY_MENU PrintMenu() {
	MY_MENU input = 0;

	printf("[1]Search\t[2]Insert\t[3]Update\t[4]Delete\t[5]Print\t[6]FilePrint\t[0]Exit\n");
	scanf_s("%d%*c", &input);
	return input;
}

void EventLoopRun() {

	int (*functionArray[6])(void) = { Search, Insert, Update, Delete, Print, FilePrint };

	MY_MENU menu = 0;

	while ((menu = PrintMenu()) != 0) {
		functionArray[menu - 1]();
	}
}

void PrintList() {
	printf("\nPrint Test\n");
	USERDATA* pTmp = &g_HeadNode;
	while (pTmp != NULL) {
		printf("[%p] %s, %s, %s, %s, [%p]\n", pTmp, pTmp->name, pTmp->address, pTmp->phone, pTmp->active, pTmp->pNext);
		pTmp = pTmp->pNext;
	}
}

void Search(void) {
	char name[32] = { 0 }, phone[32] = { 0 };
	puts("�̸� �˻��� 1, ��ȭ��ȣ �˻��� 2, �̸��� ��ȭ��ȣ �˻��� 3�� �Է����ּ���");
	int num = 0;
	scanf_s("%d%*c", &num);
	USERDATA* pResult = NULL;
	USERDATA** pResultLists = NULL;
	int result = 0;
	switch (num) {
		case 1:
			pResultLists = NULL;
			printf("name: ");
			gets_s(name, sizeof(name));
			pResultLists = SearchByNames(name);
			break;
		case 2:
			pResult = NULL;
			printf("phone: ");
			gets_s(phone, sizeof(phone));
			pResult = SearchByPhone(phone, NULL);
			break;
		case 3:
			pResult = NULL;
			printf("name and phone: ");
			scanf_s("%s%s", name, 32, phone, 32);
			pResult = SearchByNameAndPhone(name, phone, NULL);
			break;
	}

	if (pResultLists != NULL) PrintList();
	else if (pResult != NULL) PrintList();
	else puts("Not found");
}

void Insert(void) {
	char name[32] = { 0 }, address[32] = { 0 }, phone[32] = { 0 }, active[5] = { 0 };
	active[0] = '1';
	active[1] = '\r';
	active[2] = '\n';
	active[3] = '\0';

	memset(name, 0, sizeof(name));
	memset(address, 0, sizeof(address));
	memset(phone, 0, sizeof(phone));
	printf("�̸�, �ּ�, ��ȭ��ȣ�� �Է����ּ���\n");
	printf("�̸�: ");
	scanf_s("%s%*c", name, 32);
	printf("�ּ�: ");
	gets_s(address, 32);
	printf("��ȭ��ȣ: ");
	scanf_s("%s%*c", phone, 32);
	if (ValidationPhone(phone) == 1) {
		puts("�Է��� ��ȣ�� �̹� �����մϴ�.");
		return;
	}
	
	AddNewNode(name, address, phone, active);
	SaveToFile(name, address, phone, active);
	PrintList();
}

void Update(void) {
	int num = 0;
	char name[32] = { 0 }, phone[32] = { 0 };
	printf("������ ���� ���� �̸��� ��ȭ��ȣ�� �Է��� �ּ���\n");
	printf("�̸�: ");
	scanf_s("%s%*c", name, 32);
	printf("��ȭ��ȣ: ");
	scanf_s("%s%*c", phone, 32);

	char newName[32] = { 0 }, newAddress[32] = { 0 }, newPhone[32] = { 0 }, active[5] = { 0 };
	active[0] = '1';
	active[1] = '\r';
	active[2] = '\n';
	active[3] = '\0';
	while (1) {
		memset(newName, 0, sizeof(newName));
		memset(newAddress, 0, sizeof(newAddress));
		memset(newPhone, 0, sizeof(newPhone));
		printf("������ ���� �̸�, �ּ�, ��ȭ��ȣ�� �Է��� �ּ���\n");
		printf("�̸�: ");
		scanf_s("%s%*c", newName, 32);
		printf("�ּ�: ");
		gets_s(newAddress, 32);
		printf("��ȭ��ȣ: ");
		scanf_s("%s%*c", newPhone, 32);
		if (strcmp(phone, newPhone) != 0) {
			if (ValidationPhone(newPhone) == 1) {
				puts("�Է��� ��ȣ�� �̹� �����մϴ�. �ٽ� �Է��� �ּ���.");
				continue;
			}
			else break;
		}
		else break;
	}
	
	int fpPos = 0;
	USERDATA* pTmp = SearchByNameAndPhone(name, phone, &fpPos);
	if (pTmp == NULL) {
		puts("������ �ش� ����ڰ� �����ϴ�.");
	}
	else UpdateToFile(newName, newAddress, newPhone, active, pTmp, fpPos - 1);
}

void Delete(void) {
	char phone[32] = { 0 };
	printf("�����Ϸ��� ������� ��ȭ��ȣ�� �Է����ּ���: ");
	scanf_s("%s%*c", phone, 32);
	int fpPos = 0;
	USERDATA* pTmp = SearchToRemove(phone, &fpPos);
	if (pTmp == NULL) {
		puts("��ȭ��ȣ�� ��ġ�ϴ� ����ڰ� �����ϴ�.");
	}
	else {
		pTmp->active[0] = '0';
		pTmp->active[1] = '\r';
		pTmp->active[2] = '\n';
		pTmp->active[3] = '\0';
		RemoveFromFile(pTmp, fpPos - 1);
	}
}

void Print(void) {
	PrintList();
}

void FilePrint(void) {
	ReadFromFile();
}