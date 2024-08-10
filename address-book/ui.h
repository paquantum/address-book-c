#pragma once

typedef enum MY_MENU { QUIT, SELECT, INSERT, UPDATE, DELETE, PRINTNODE, PRINTFILE } MY_MENU;

MY_MENU PrintMenu();
void EventLoopRun();
void PrintList();
void Search(void);
void Insert(void);
void Update(void);
void Delete(void);
void PrintNode(void);
void PrintFile(void);