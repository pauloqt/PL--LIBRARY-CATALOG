
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>



void SetColor(int ForgC);
void gotoxy(int x,int y);
void setFontStyle(int FontSize);
void ShowConsoleCursor(int showFlag);

int main(){
    setFontStyle(23);
    char Menu[][31] =  {"  ADD STUDENT  ", " DELETE STUDENT ", " UPDATE STUDENT ", "DISPLAY STUDENTS", "  EXIT & SAVE  "};
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        system("cls");
        ShowConsoleCursor(0);//SET CURSOR OFF
        gotoxy(52,8);
        printf( "MAIN MENU\n\n");
        gotoxy(35, 16);
        printf("USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU");


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
            }else if(ch=getch() == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(1);//SET CURSON ON
                        //userAddStudent();
                        printf(" Add Student Record\n");
                        system("pause");
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        //userDeleteStudent();
                        printf(" Delete Student Record\n");
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        ShowConsoleCursor(1);
                        //userUpdateStudent();
                        printf(" Add Student Record\n");
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        ShowConsoleCursor(1);
                        //userDisplayStudents();
                        printf(" Add Student Record\n");
                        system("pause");
                        break;

                    }
                    case 4:
                    {
                        ShowConsoleCursor(1);
                        //STUDENTS.saveRecords();
                        //exitMessage();
                       printf(" Return home\n");
                        system("pause");
                        exit(0);
                    }
                }
                break;
            }
        }

    }
}
void gotoxy(int x,int y){
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

void ShowConsoleCursor(int showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
/*
Black        |   0
Blue         |   1
Green        |   2
Cyan         |   3
Red          |   4
Magenta      |   5
Brown        |   6
Light Gray   |   7
Dark Gray    |   8
Light Blue   |   9
Light Green  |   10
Light Cyan   |   11
Light Red    |   12
Light Magenta|   13
Yellow       |   14
White        |   15*/
