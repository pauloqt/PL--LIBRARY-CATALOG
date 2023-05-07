#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

void SetColor(int ForgC);
void gotoxy(int x,int y);
void setFontStyle(int FontSize);
void ShowConsoleCursor(bool showFlag);

int main(){
    setFontStyle(23);
    string Menu[5] =  {"  ADD STUDENT  ", " DELETE STUDENT ", " UPDATE STUDENT ", "DISPLAY STUDENTS", "  EXIT & SAVE  "};
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(true){
        system("cls");
        ShowConsoleCursor(false);
        gotoxy(52,8);
        cout << "MAIN MENU\n\n";
        gotoxy(35, 16);
        cout<<"USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU";


        for(int i=0; i<5; ++i){
            //This will highlight the choice in the menu
            if(i==pointer){
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 1);
                cout << Menu[i] << endl;
            }else{
                gotoxy(48,10+i);
                SetConsoleTextAttribute(hConsole, 15); // set color of the text to white
                cout << Menu[i] << endl;
            }
             SetConsoleTextAttribute(hConsole, 15);
        }
        //This will check the key stroke that is being pressed in keyboard
        while(true){
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
                        ShowConsoleCursor(true);
                        //userAddStudent();
                        cout <<" Add Student Record\n";
                        system("pause");
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(true);
                        //userDeleteStudent();
                        cout <<" Delete Student Record\n";
                        system("pause");
                        break;
                    }
                    case 2:
                    {
                        ShowConsoleCursor(true);
                        //userUpdateStudent();
                        cout <<" Add Student Record\n";
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        ShowConsoleCursor(true);
                        //userDisplayStudents();
                        cout <<" Add Student Record\n";
                        system("pause");
                        break;

                    }
                    case 4:
                    {
                        ShowConsoleCursor(false);
                        //STUDENTS.saveRecords();
                        //exitMessage();
                        cout <<" Return home\n";
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
    std::wcscpy(cfi.FaceName, L"Consolas"); // font style
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
