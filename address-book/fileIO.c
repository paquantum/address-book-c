#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "fileIO.h"

int ReadFromFile() {
	FILE* fp = NULL;
	fopen_s(&fp, "user_info.dat", "rb");
	if (fp == NULL) {
		puts("ERROR: Not Found File");
		return NULL;
	}

	USERDATA user = { 0 };
	int cnt = 0;
	while (fread(&user, sizeof(USERDATA), 1, fp) > 0) {
		printf("name: %s, address: %s, phone: %s, active: %s", user.name, user.address, user.phone, user.active);
		memset(&user, 0, sizeof(user));
		cnt++;
	}
	printf("\n");
	
	fclose(fp);

	return cnt;
}

void ReadFromFile2(int cnt) {
	FILE* fp2 = NULL;
	fopen_s(&fp2, "user_info.dat", "rb+");
	if (fp2 == NULL) {
		puts("ERROR: Not Found File");
		return NULL;
	}
	cnt--;
	rewind(fp2);
	fseek(fp2, sizeof(USERDATA) * cnt, SEEK_SET);
	printf("파일포인터 위치: %d\n", ftell(fp2));
	
	USERDATA user = { 0 };
	memset(&user, 0, sizeof(user));
	strcpy_s(user.name, sizeof(user.name), "우시하2");
	strcpy_s(user.address, sizeof(user.address), "남군 중계다요");
	strcpy_s(user.phone, sizeof(user.phone), "010-2167-0000");
	fwrite(&user, sizeof(USERDATA), 1, fp2);

	fclose(fp2);
}

// 기존 파일에서 데이터를 읽고 USERDATA 타입 변수에 저장한 후 파일로 쓰기
void ImigrationFile() {
	FILE* srcFp = NULL;
	fopen_s(&srcFp, "dummy_data.txt", "rb");
	if (srcFp == NULL) return;
	FILE* dstFp = NULL;
	fopen_s(&dstFp, "user_info.dat", "wb");
	if (dstFp == NULL) return;

	USERDATA user = { 0 };
	char* context = NULL;
	char buffer[195] = { 0 };
	char* token;
	int i = 0, idx = 0;
	while (!feof(srcFp)) {
		memset(&user, 0, sizeof(user));
		user.active[0] = '1';
		user.active[1] = '\r';
		user.active[2] = '\n';
		i = 0;
		fgets(buffer, 192, srcFp); // 파일에서 한 줄 읽음, [이름, 주소, 전화번호]
		token = strtok_s(buffer, ",", &context); // , 를 기준으로 앞의 값을 token에 저장
		while (token != NULL) {
			if (i == 0) strcpy_s(user.name, sizeof(user.name), token);
			else if (i == 1) strcpy_s(user.address, sizeof(user.address), token);
			else if (i == 2) strcpy_s(user.phone, sizeof(user.phone), token);
			i++;
			token = strtok_s(NULL, ",", &context);
		}
		idx++;
		fwrite(&user, sizeof(USERDATA), 1, dstFp);
	}
	fclose(srcFp);
	fclose(dstFp);
}

void WriteToFileTest() {
	FILE* fp = NULL;
	fopen_s(&fp, "dummy.txt", "ab");
	if (fp == NULL) return;
	USERDATA user = { 0 };

	strcpy_s(user.name, sizeof(user.name), "houhou");
	strcpy_s(user.address, sizeof(user.address), "Seoul Mapo-go ahyeon");
	strcpy_s(user.phone, sizeof(user.phone), "010-1111-1111");
	fwrite(&user, sizeof(USERDATA), 1, fp);


	fclose(fp);
}