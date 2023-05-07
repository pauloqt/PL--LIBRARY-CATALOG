#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include "bookFunctions.c"
#include "borrowerFunctions.c"
#include "transactionFunctions.c"
#include "designFunctions.c"

HWND WINAPI GetConsoleWindowNT(void);
//PARA SA LAHAT

//The gotoxy() function is used to position the console cursor to a specified location, with the x-coordinate and y-coordinate specified as arguments.
void gotoxy(int x,int y){   //A function that Sets the fixed place of displays
    COORD coord = {0,0};
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void SetColor(int ForgC){
  WORD wColor;

  HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFO csbi;

                       //We use csbi for the wAttributes word.
 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
 {
                 //Mask out all but the background attribute, and add in the forgournd color
      wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      SetConsoleTextAttribute(hStdOut, wColor);
 }
 return;
}

void setFontStyle(int FontSize){
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;                   // Width of each character in the font
    cfi.dwFontSize.Y = FontSize;                  // Height
    cfi.FontFamily = FF_DONTCARE;

    cfi.FontWeight = FW_NORMAL;
    wcscpy(cfi.FaceName, L"Consolas"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

//Sets a fixed window size
HWND WINAPI GetConsoleWindowNT(void)
{
    //declare function pointer type
    typedef HWND WINAPI(*GetConsoleWindowT)(void);
    //declare one such function pointer
    GetConsoleWindowT GetConsoleWindow;
    //get a handle on kernel32.dll
    HMODULE hk32Lib = GetModuleHandle(TEXT("KERNEL32.DLL"));
    //assign procedure address to function pointer
    GetConsoleWindow = (GetConsoleWindowT)GetProcAddress(hk32Lib
    ,TEXT("GetConsoleWindow"));
    //check if the function pointer is valid
    //since the function is undocumented
    if(GetConsoleWindow == NULL){
        return NULL;
    }
    //call the undocumented function
    return GetConsoleWindow();
}

void studentPortalMenu(){

BOOK *p;
setFontStyle(18);
char Menu[][50] =  {"\n\n\n\n\n\t\t\t\t\t\t\tDISPLAY ALL BOOKS  ", "\n\n\n\n\n\t\t\t\t\t\t\tSEARCH BOOKS ", "\n\n\n\n\n\t\t\t\t\t\t\tBORROW BOOKS ", "\n\n\n\n\n\t\t\t\t\t\t\tCHANGE PASSWORD ", "\n\n\n\n\n\t\t\t\t\t\t\tGO BACK ","\n\n\n\n\n\t\t\t\t\t\t\tEXIT " };
int pointer = 0;
const char ENTER = 13;//ASCII code for ENTER Key
char ch = ' ';
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        system("cls");
        dispStudentPortal();
        ShowConsoleCursor(0);//SET CURSOR OFF

        for(int i=0; i<6; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(48,10+i);

                SetConsoleTextAttribute(hConsole, 10);

                printf("%s\n", Menu[i]);
            }else{
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                printf("%s\n",Menu[i]);
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(1){
            if(GetAsyncKeyState(VK_UP) != 0){
                --pointer;

                if(pointer == -1){
                    pointer = 5;
                    }
                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 6){
                    pointer = 0;
                }

                break;
            }else if((ch = getch()) == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(1);//SET CURSON ON
                        system("cls");
                        dispAllBooks();
                        displayBook(p=headBook, 0, NULL);
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        system("cls");
                        dispSearchBooks();
                        searchBook();//AFTER MAGPROMPT NG ENTER PAKILAGYAN NG LOADING BEFORE MAG SYSTEM CLS
                        break;
                    }

                    case 2:
                    {
                        ShowConsoleCursor(1);
                        system("cls");
                        borrowMenu();
                        break;
                    }
                    case 3:
                    {
                        ShowConsoleCursor(1);
                        //dispChangePass();
                        changePassBorrower();//ANG MGA PRINTF NI USER DAPAT NASA SPACE NEED IGOTOXY
                        break;
                    }
                    case 4:
                    {
                        ShowConsoleCursor(1);
                        return; //return
                        break;
                    }
                    case 5:
                    {
                        ShowConsoleCursor(1);
                        printf(" EXITING PROGRAM.... ");//NEED LOADING BAR
                        system("pause");
                        exit(0);
                    }

                  }
                }
                break;
            }
        }
}


void adminPortalMenu(){
setFontStyle(18);
char Menu[][50] =  {"\n\n\n\n\n\t\t\t\t\t\t\tMANAGE BOOK RECORD  ", "\n\n\n\n\n\t\t\t\t\t\t\tMANAGE BORROWING RECORD ", "\n\n\n\n\n\t\t\t\t\t\t\tMANAGE BORROWER RECORD ", "\n\n\n\n\n\t\t\t\t\t\t\tGO BACK ","\n\n\n\n\n\t\t\t\t\t\t\tEXIT " };
int pointer = 0;
const char ENTER = 13;//ASCII code for ENTER Key
char ch = ' ';
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        system("cls");
        dispAdminPortal();
        ShowConsoleCursor(0);//SET CURSOR OFF
        for(int i=0; i<5; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 10);
                printf("%s\n", Menu[i]);
            }else{
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                printf("%s\n",Menu[i]);
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(1){
            if(GetAsyncKeyState(VK_UP) != 0){
                --pointer;
                if(pointer == -1){
                    pointer = 4;
                    }
                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 5){
                    pointer = 0;
                }
                break;
            }else if((ch = getch()) == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(1);//SET CURSON ON
                        manageBookMenu();
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        manageBorrowingMenu();
                        break;
                    }

                    case 2:
                    {
                        ShowConsoleCursor(1);
                        manageBorrowerMenu();
                        break;
                    }

                    case 3:
                    {
                        ShowConsoleCursor(1);
                        return;
                        break;
                    }
                    case 4:
                    {
                        ShowConsoleCursor(1);
                        system("cls");
                        printf(" EXITING PROGRAM.... ");//NEED LOADING BAR
                        system("pause");
                        exit(0);
                    }
                  }
                }
                break;
            }
        }
}

int main(){
HWND hWnd=GetConsoleWindowNT();
MoveWindow(hWnd,900,900,2000,2000,TRUE);
int optionPortal, optionAdmin, optionStudent;
//for pull down
setFontStyle(18);
char Menu[][50] =  {"\n\n\n\n\n\t\t\t\t\t\t\tSTUDENT PORTAL\n  ", "\n\n\n\n\n\t\t\t\t\t\t\tADMIN PORTAL\n ", "\n\n\n\n\n\t\t\t\t\t\t\tEXIT\n " };
int pointer = 0;
const char ENTER = 13;//ASCII code for ENTER Key
char ch = ' ';
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    headBook=NULL;                   //initializing linked list.
    headBorrower=NULL;
    headTransaction=NULL;

    retrieveBook();                  //retrieve all previous records.
    retrieveBorrower();
    retrieveTransaction();

        while(1){
        system("cls");
        mainFront();
        ShowConsoleCursor(0);//SET CURSOR OFF

        for(int i=0; i<3; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(48,10+i);

                SetConsoleTextAttribute(hConsole, 10);
                printf("%s\n", Menu[i]);
            }else{
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                printf("%s\n",Menu[i]);
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(1){
            if(GetAsyncKeyState(VK_UP) != 0){
                --pointer;

                if(pointer == -1){
                    pointer = 2;
                    }

                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 3){
                    pointer = 0;
                }

                break;
            }else if((ch = getch()) == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(1);//SET CURSON ON
                        studentPortalMenu();
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        adminPortalMenu();
                        break;
                    }

                    case 2:
                    {
                        ShowConsoleCursor(1);
                        printf(" EXITING PROGRAM.... ");//PAKILAKIHAN ANG FONT AND MAGLAGAY NG LOADING SA BABA NETO
                       // TINANGGAL KO NA ANG SYSTEM PAUSE KAPALIT NG LOADING
                        exit(0);
                    }
                  }
                }
                break;
            }
        }
}
