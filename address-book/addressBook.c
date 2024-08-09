#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"
#include "ui.h"
#include "test.h"
#include "fileIO.h"

int main()
{
	InitList();

	// faker js로 생성한 데이터 옮겨오기용
	//ImigrationFile();
	//ReadFromFile();
	//FirstDataSearchTimeTest();
	//LastDataSearchTimeTest();
	
	//InitDummyData();
	EventLoopRun();

	//ReleaseList();
}