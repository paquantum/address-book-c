#pragma once

typedef enum MY_MENU { SELECT, INSERT, UPDATE, DELETE, PRINT, FILEPRINT, QUIT } MY_MENU;

MY_MENU PrintMenu();
void EventLoopRun();
void PrintList();
void Search(void);
void Insert(void);
void Update(void);
void Delete(void);
void Print(void);
void FilePrint(void);