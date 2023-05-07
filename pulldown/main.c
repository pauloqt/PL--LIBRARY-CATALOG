#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>


void SetColor(int ForgC);
void gotoxy(int x,int y);
void setFontStyle(int FontSize);
void ShowConsoleCursor(int showFlag);
void mainFront();
void studentPortalMenu();
void adminPortalMenu();
void searchMenu();

int main(){

    mainFront();

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
void mainFront(){


    setFontStyle(23);
    char Menu[][31] =  {" \nSTUDENT PORTAL\n  ", "  \nADMIN PORTAL\n ", "  \nEXIT\n " };
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("---------------------");
    printf("|                   |");
    printf("---------------------");
    printf("---------------------");
    printf("|                   |");
    printf("---------------------");
    printf("---------------------");
    printf("|                   |");
    printf("---------------------");

    while(1){
        system("cls");
        ShowConsoleCursor(0);//SET CURSOR OFF
        gotoxy(52,8);
        /*printf("   oooooooooooo  ooooo     ooo ooooooooo.        ooooooooo.  oooooooooooo       .o.       oooooooooo.    .oooooo..o");
        printf("\n 8'  888   `8 `888'     `8' `888   `Y88.      `888   `Y88. `888'     `8      .888.      `888'   `Y8b  d8P'    `Y8");
        printf("\n     888       888       8   888   .d88'       888   .d88'  888             .8\"888.     888      888 Y88bo.   ");
        printf("\n     888       888       8   888ooo88P'        888ooo88P'   888oooo8       .8' `888.     888      888  `\"Y8888o.");
        printf("\n     888       888       8   888               888`88b.     888    \"     .88ooo8888.    888      888     `\"Y88b ");
        printf("\n     888       `88.    .8'   888               888  `88b.   888       o  .8'     `888.   888     d88' oo     .d8P");
        printf("\n    o888o        `YbodP'    o888o             o888o  o888o o888ooooood8 o88o     o8888o o888bood8P'   8\"\"88888P\"");
*/
        printf("  __\n");
        printf(" (`/\\`\n");
        printf(" `=\\/\\ __...--~~~~~-._   _.-~~~~~--...__\n");
        printf("  `=\\/\\               \\ /               \\\n");
        printf("   `=\\/                  V                 \\\n");
        printf("   //_\\___--~~~~~~-._    |  _.-~~~~~~--...__\\\\\n");
        printf("  //  ) (..----~~~~._\\   | /_.~~~~----.....__\\\\\n");
        printf(" ===( INK )==========\\\\ |//====================\n");
        printf("    \\___/\n");

        gotoxy(35, 16);
        printf("USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU");


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
                        //userAddStudent();
                        printf("  ___ _____ _   _ ___  ___ _  _ _____   ___  ___  ___ _____ _   _\n");
                        printf("/ __|_   _| | | |   \\| __| \\| |_   _| | _ \\/ _ \\| _ \\_   _/_\\ | |\n");
                        printf("\\__ \\ | | | |_| | |) | _|| .` | | |   |  _/ (_) |   / | |/ _ \\| |__\n");
                        printf("|___/ |_|  \\___/|___/|___|_|\\_| |_|   |_|  \\___/|_|_\\ |_/_/ \\_\\____|\n");


                        studentPortalMenu();
                        system("pause");
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        printf("    _   ___  __  __ ___ _  _   ___  ___  ___ _____ _   _    \n");
                        printf("   /_\\ |   \\|  \\/  |_ _| \\| | | _ \\/ _ \\| _ \\_   _/_\\ | |   \n");
                        printf("  / _ \\| |) | |\\/| || || .` | |  _/ (_) |   / | |/ _ \\| |__ \n");
                        printf(" /_/ \\_\\___/|_|  |_|___|_|\\_| |_|  \\___/|_|_\\ |_/_/ \\_\\____|\n");

                        adminPortalMenu();
                        system("pause");
                        break;
                    }

                    case 2:
                    {
                        ShowConsoleCursor(1);
                        //STUDENTS.saveRecords();
                        //exitMessage();
                       printf(" EXIT ");
                        system("pause");
                        exit(0);
                    }
                }
                }
                break;
            }
        }

    }



void studentPortalMenu(){


    setFontStyle(23);
    char Menu[][31] =  {" DISPLAY ALL BOOKS  ", "  SEARCH BOOKS ", "  BORROW BOOKS ", " CHANGE PASSWORD ", " GO BACK "," EXIT " };
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    while(1){
        system("cls");
        ShowConsoleCursor(0);//SET CURSOR OFF
        gotoxy(35, 16);printf("USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU");


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
                        //userAddStudent();
                        system("cls");
                        printf("  ___ ___ ___ ___ _      ___   __    _   _    _      ___  ___   ___  _  _____ \n");
                        printf(" |   \\_ _/ __| _ \\ |    /\\_ \\ / /   /\\_ \\| |  | |    | _ )/ _ \\ / _ \\| |/ / __|\n");
                        printf(" | |) | |\\__ \\  _/ |__ / _ \\ V /   / _ \\| |__| |__  | _ \\ (_) | (_) | ' <\\__ \\\n");
                        printf(" |___/___|___/_| |____/\\_/ \\_\\_|   /_/ \\_\\____|____| |___/\\___/ \\___/|_|\\_\\___/\n");



//DONE
                        //FUNCITON NG DISPLAY ALL BOOKS
                        system("pause");
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        //userDeleteStudent();
                        printf("  ___ ___   _   ___  ___ _  _   ___  ___   ___  _  _____ \n");
                        printf(" / __| __| /_\\ | _ \\/ __| || | | _ )/ _ \\ / _ \\| |/ / __|\n");
                        printf(" \\__ \\ _| / _ \\|   / (__| __ | | _ \\ (_) | (_) | ' <\\__ \\\n");
                        printf(" |___/___/_/ \\_\\_|_\\\\___|_||_| |___/\\___/ \\___/|_|\\_\\___/\n");

                        //FUNCTION NG SEARCH BOOKS
                        searchMenu();
                        system("pause");
                        break;
                    }

                    case 2:
                    {
                       ShowConsoleCursor(1);
                        //userDeleteStudent();
                        printf("  ___  ___  ___ ___  _____      __  ___  ___   ___  _  _____ \n");
                        printf(" | _ )/ _ \\| _ \\ _ \\/ _ \\ \\    / / | _ \\/ _ \\ / _ \\| |/ / __|\n");
                        printf(" | _ \\ (_) |   /   / (_) \\ \\/\\/ /  | _ \\ (_) | (_) | ' <\\__ \\\n");
                        printf(" |___/\\___/|_|_\\_|_\\\\___/ \\_/\\_/   |___/\\___/ \\___/|_|\\_\\___/\n");




                        //FUNCTION NG BORROW BOOKS
                        system("pause");
                        break;
                    }
                    case 3:
                    {
                        ShowConsoleCursor(1);
                        //userDeleteStudent();
                        printf("   ___ _  _   _   _  _  ___ ___   ___  _   ___ _____      _____  ___ ___  \n");
                        printf("  / __| || | /_\\ | \\| |/ __| __| | _ \\/_\\ / __/ __\\ \\    / / _ \\| _ \\   \\ \n");
                        printf(" | (__| __ |/ _ \\| .` | (_ | _|  |  _/ _ \\\\__ \\__ \\\\ \\/\\/ / (_) |   / |) |\n");
                        printf("  \\___|_||_/_/ \\_\\_|\\_|\\___|___| |_|/_/ \\_\\___/___/ \\_/\\_/ \\___/|_|_\\___/\n");

                         printf(" *****************************************************\n");
                         printf(" *                                                   *\n");
                         printf(" * ==================================================*\n");
                         printf(" * |    TUP ID    |                                  *\n");
                         printf(" * ==================================================*\n");
                         printf(" *                                                   *\n");
                         printf(" * ==================================================*\n");
                         printf(" * | NEW PASSWORD |                                  *\n");
                         printf(" * ==================================================*\n");
                         printf(" *                                                   *\n");
                         printf(" * ==================================================*\n");
                         printf(" * |RE-ENTER PASSWORD |                              *\n");
                         printf(" * ==================================================*\n");
                         printf(" *                                                   *\n");
                         printf(" *****************************************************\n\n ");

                        system("pause");
                        break;
                    }
                    case 4:
                    {
                        ShowConsoleCursor(1);
                        //userDeleteStudent();

                        mainFront();
                        system("pause");
                        break;
                    }
                    case 5:
                    {
                         ShowConsoleCursor(1);
                        //STUDENTS.saveRecords();
                        //exitMessage();
                        printf(" EXIT ");
                        system("pause");
                        exit(0);
                    }

                  }
                }
                break;
            }
        }


}
void searchMenu(){
    printf("\033[5;1m%s\033[0m\n", "SEARCH BOOKS");

}
void borrowMenu(){

 setFontStyle(23);
    char Menu[][31] =  {" LOGIN  ", "  REGISTER "};
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    printf("---------------------");
    printf("|                   |");
    printf("|                   |");
    printf("---------------------");
    printf("---------------------");
    printf("|                   |");
    printf("|                   |");
    printf("---------------------");

    while(1){
        system("cls");
        ShowConsoleCursor(0);//SET CURSOR OFF
        gotoxy(35, 16);printf("USE UP OR DOWN ARROW KEYS TO NAVIGATE THROUGH MENU");


        for(int i=0; i<2; ++i){
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
                    pointer = 1;
                    }

                break;
            }else if(GetAsyncKeyState(VK_DOWN) != 0){
                ++pointer;
                if(pointer == 2){
                    pointer = 0;
                }

                break;
            }else if((ch = getch()) == ENTER){
                switch(pointer){
                    case 0:
                    {
                        ShowConsoleCursor(1);//SET CURSON ON
                        //userAddStudent();
                        system("cls");
                        printf("  _    ___   ___ ___ _  _ \n ");
                        printf(" | |  / _ \\ / __|_ _| \\| |\n  ");
                        printf(" | |_| (_) | (_ || || .` |\n  ");
                        printf(" |____\\___/ \\___|___|_|\\_|\n  ");



                        //FUNCITON NG LOGIN
                        system("pause");
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        //userDeleteStudent();
                        printf("  ___ ___ ___ ___ ___ _____ ___ ___ \n");
                        printf(" | _ \\ __/ __|_ _/ __|_   _| __| _ \\ \n");
                        printf(" |   / _| (_ || |\\__ \\ | | | _||   / \n");
                        printf(" |_|_\\___\\___|___|___/ |_| |___|_|_\\ \n");
                        printf("\n\n");
                        printf("---------------------------------------------------------\n");
                        printf("| ---------------------  |                              |\n");
                        printf("| |                   |  |  __________________________  |\n");
                        printf("| |     _________     |  |  	      NAME	            |\n");
                        printf("| |    /         \\    |  |  __________________________ |\n");
                        printf("| |   |           |   |  |           TUP-ID             |\n");
                        printf("| |   |           |   |  |  __________________________  |\n");
                        printf("| |  __\\_________/__  |  |        YEAR & SECTION       |\n");
                        printf("| | /               \\ |  |  __________________________ |\n");
                        printf("| | |               | |  |         CONTACT NO.          |\n");
                        printf("| | |               | |  |  __________________________  |\n");
                        printf("| ---------------------  |           EMAIL              |\n");
                        printf("---------------------------------------------------------\n");


                        //FUNCTION NG REGISTER

                        system("pause");
                        break;
                    }
              }
         }
       }
    }
}
void adminPortalMenu(){


}
