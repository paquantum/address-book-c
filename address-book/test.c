#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "list.h"
#include "ui.h"

void FirstDataSearchTimeTest() {
	double start, end;

	start = (double)clock();
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb");
	if (fp == NULL) {
		puts("ERROR: Not Found File");
		return;
	}
	USERDATA user = { 0 };
	fread(&user, sizeof(USERDATA), 1, fp);
	end = (double)clock();
	fclose(fp);
	
	printf("���� ù��° �ڷ� �˻� �ӵ�: %lf\n", (end - start) / CLOCKS_PER_SEC);
}

void LastDataSearchTimeTest() {
	double start, end;

	start = (double)clock();
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb");
	if (fp == NULL) {
		puts("ERROR: Not Found File");
		return;
	}
	USERDATA user = { 0 };
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0) {  }
	end = (double)clock();
	fclose(fp);

	printf("���� ������ �ڷ� �˻� �ӵ�: %lf\n", (end - start) / CLOCKS_PER_SEC);
}

void TestStep01() {
	puts("===TestStep01(): First Element Delete");
	AddNewNode("hoon", "���� ������", "010-1111-1111", "1");
	AddNewNode("houhou", "���� ��������", "010-2222-2222", "1");
	AddNewNode("storm stm", "�λ� ����", "010-3333-3333", "1");
	PrintList();

	USERDATA* pPrev = SearchByName("010-1111-1111");
	if (pPrev != NULL)
		RemoveNode(pPrev);

	ReleaseList();
	putchar('\n');
}

void TestStep02() {
	puts("===TestStep02(): Second Element Delete");
	AddNewNode("hoon", "���� ������", "010-1111-1111", "1");
	AddNewNode("houhou", "���� ��������", "010-2222-2222", "1");
	AddNewNode("storm stm", "�λ� ����", "010-3333-3333", "1");
	PrintList();

	USERDATA* pPrev = SearchByName("010-2222-2222");
	if (pPrev != NULL)
		RemoveNode(pPrev);

	ReleaseList();
	putchar('\n');
}

void TestStep03() {
	puts("===TestStep03(): Third Element Delete");
	AddNewNode("hoon", "���� ������", "010-1111-1111", "1");
	AddNewNode("houhou", "���� ��������", "010-2222-2222", "1");
	AddNewNode("storm stm", "�λ� ����", "010-3333-3333", "1");
	PrintList();

	USERDATA* pPrev = SearchByName("010-3333-3333");
	if (pPrev != NULL)
		RemoveNode(pPrev);

	ReleaseList();
	putchar('\n');
}

void InitDummyData() {
	printf("\nInit Dummy data\n");
	AddNewNode("hoon", "���� ������", "010-1111-1111", "1");
	AddNewNode("houhou", "���� ��������", "010-2222-2222", "1");
	AddNewNode("storm stm", "�λ� ����", "010-3333-3333", "1");
	PrintList();
}