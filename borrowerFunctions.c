#include "borrowerFunctions.h"


//FOR BORROWER FUNCTIONS
//locateTUP_ID() accepts the TUP_ID as parameter then locates the node with the TUP_ID in the borrower linked list, then returns the node.
BORROWER *locateTUP_ID(char TUP_ID[]){
BORROWER *p;

    p=headBorrower;
        while(p!=NULL && strcmp(p->TUP_ID, TUP_ID)!=0){
        p=p->nxt;
    }
    return p;
}

//passDisp() allows the user to enter password in encrypted display.
void passDisp(){

    int index = 0;
    char ch;

    while((ch=getch())!=13 && index<7){
        if (index<0)
            index=0;
        if(ch==8){//backspace ascii is 8
            putch('\b');
            putch(' ');
            putch('\b');
            index--;
         continue;
        }
        if(isdigit(ch)){
         encryptedPass[index++]=ch;
         putchar('*');
        }
    }
    if (index==7)
        encryptedPass[index++]=ch;
    encryptedPass[index]='\0';
}

//The getInfoBorrower() function prompts the student to enter their information for registration including all details from the Struct borrower. It stores this information in the infoBorrower struct variable.
void getInfoBorrower(){
    char rePass[14];
    system("cls");
    dispRegister();
    gotoxy(55,15); printf("COMPLETE THE INFORMATION BELOW\n\n");
    gotoxy(55,16); printf("TUP ID (Ex. 123456): TUP-M ");
    scanf("%s", &infoBorrower.TUP_ID);
    if(locateTUP_ID(infoBorrower.TUP_ID)!=NULL){
        gotoxy(54,17); printf("YOUR TUP ID IS ALREADY REGISTERED!"); gotoxy(54,18);system("pause"); system("cls");
    }
    else{
        PASS:
        gotoxy(55,17); printf("PASSWORD: ");
        passDisp();
        strcpy(infoBorrower.password, encryptedPass);
        gotoxy(55,18); printf("RE-ENTER PASSWORD: ");
        passDisp();
        strcpy(rePass, encryptedPass);
        if(strcmp(rePass, infoBorrower.password)==0){
                gotoxy(55,19); printf("NAME (EX. JUAN A. DELA CRUZ): ");
                fflush stdin;
                scanf("%[^\n]", &infoBorrower.name);
                fflush stdin;
                gotoxy(55,20); printf("COURSE AND SECTION (EX: BSCS-NS2A): ");
                scanf("%s", &infoBorrower.yearSection);
                gotoxy(55,21); printf("CONTACT NUMBER (Ex. 09123456789): ");
                scanf("%s", &infoBorrower.contactNum);
                gotoxy(55,22); printf("EMAIL ADDRESS (Ex. juandelacruz@tup.edu.ph): ");
                scanf("%s", &infoBorrower.email);
                gotoxy(55,23); printf("YOUR ACCOUNT IS SUCCESSFULLY REGISTERED!");
                gotoxy(55,24); system("pause");
                return;
        }
        else{
            gotoxy(56,19); printf("PASSWORD DIDN'T MATCH");
            system("pause"); system("cls");
            goto PASS;
        }
    }
}

//The addBorrower()  adds a new node to the book linked list in alphabetical order, with the infoBorrwer struct as its data.
int addBorrower(){
BORROWER *q, *p, *n;

     n= (BORROWER*)malloc(sizeof(BORROWER));    //allocates memory to n.
    *n= infoBorrower;                           //copy info of the book to n.

    p=q=headBorrower;                           //point all pointers to head.
    while(p!=NULL && strcmp(infoBorrower.name, p->name)>=0){
        q=p;
        p=p->nxt;
    }

    if(p==headBorrower){    //if to insert at the head.
        headBorrower=n;
    }
    else{           //if to insert in between or at the end.
        q->nxt=n;
    }
    n->nxt=p;  //insert p at the end which contains next node or NULL.
}

//saveInfoBorrower() saves the encrypted borrower details in "borrowerDetails.txt"
void saveInfoBorrower(){//"borrowerDetails.txt"

FILE *fp= fopen("borrowerDetails.txt", "w+");
BORROWER *p;

    if(fp==NULL){
        printf("\nTHE FILE ""borrowerDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }
    else{
        p=headBorrower;
        while(p!=NULL){
            //saving encrypted info.
            fprintf(fp, "%s\n%s %s %s %s %s\n\n", encrypt(p->name), encrypt(p->TUP_ID), encrypt(p->password), encrypt(p->yearSection), encrypt(p->contactNum), encrypt(p->email));
            p=p->nxt;
        }
        fclose(fp);
    }
}

//retrieve() function retrieves all info from the text file and save each book in the linked list.
void retrieveBorrower(){
FILE *fp= fopen("borrowerDetails.txt", "r+");
BOOK *p;

    if(fp==NULL){
        printf("THE FILE ""borrowerDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        while(1){
            fflush stdin;
            fscanf(fp, "\n%[^\n]\n", &infoBorrower.name);
            fflush stdin;

            fscanf(fp, "%s %s %s %s %s", infoBorrower.TUP_ID, infoBorrower.password, infoBorrower.yearSection, infoBorrower.contactNum, infoBorrower.email);

            //decrypting info..
            strcpy(infoBorrower.TUP_ID, decrypt(infoBorrower.TUP_ID)); strcpy(infoBorrower.password, decrypt(infoBorrower.password)); strcpy(infoBorrower.yearSection, decrypt(infoBorrower.yearSection));
            strcpy(infoBorrower.contactNum, decrypt(infoBorrower.email)); strcpy(infoBorrower.name, decrypt(infoBorrower.name));

            if(!feof(fp)){
                addBorrower();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

//logInBorrower() allows student to log in their existing account by entering their TUP ID and password.
BORROWER* loginBorrower(){
BORROWER *p;
char enteredID[7], enteredPass[7];
int tries=3, flag=0;

    while (tries > 0 && flag==0) {
        system("cls");

        dispLogin();
        gotoxy(55,15); printf("TUP ID (Ex. 123456): TUP-M ");
        scanf("%s", enteredID);
        gotoxy(55,16); printf("PASSWORD: ");
        passDisp();
        strcpy(enteredPass, encryptedPass);

        p=locateTUP_ID(enteredID);
        if(p!=NULL && strcmp(enteredPass, p->password)==0){     //para di need i-compare lahat ng pass, ID lang.
            gotoxy(55,18); printf("LOGIN SUCCESSFUL!"); gotoxy(55,19); system("pause");
            flag=1;
            return p->TUP_ID;
        }

        else{
            gotoxy(55,18); printf("INVALID TUP ID OR PASSWORD. ");
            tries--;
            gotoxy(55,20); printf("YOU HAVE %d TRIES LEFT.", tries);
            gotoxy(55,21); system("pause");
            system("cls");
        }
    }
    if (tries == 0) {
        gotoxy(55,21); printf("YOU HAVE EXCEEDED THE MAXIMUM NUMBER OF TRIES.");
        gotoxy(56,22); system("pause");
        studentPortalMenu();
    }

}

//changePassBorrower() allows user to change their password by asking their TUP ID, current pass, and new pass.
void changePassBorrower(){
BORROWER *p;
char currPass[14], newPass[14], rePass[14], TUP_ID[7];
int tries1=3, tries2=3, flag1=0, flag2=0;

        system("cls");
        changePass();
        gotoxy(55,15); printf("Enter your TUP ID: TUP-M ");
        scanf("%s", TUP_ID);
        p=locateTUP_ID(TUP_ID);
        if(p==NULL){
            gotoxy(55,16); printf("YOU ARE NOT REGISTERED! GO TO BORROW OPTION TO REGISTER."); system("pause");
        }

        else{
            //FOR CURRENT PASS
            while(tries1>0 && flag1==0){
                system("cls");
                changePass();
                gotoxy(55,16); printf("ENTER CURRENT PASSWORD: ");
                passDisp();
                if(strcmp(encryptedPass, p->password)==0){
                    flag1=1;

                    //FOR NEW PASS
                    while(tries2 && flag2==0){
                        system("cls");
                        changePass();
                        gotoxy(55,16); printf("ENTER NEW PASSWORD: ");
                        passDisp();
                        strcpy(newPass, encryptedPass);
                        gotoxy(55,17); printf("RE-ENTER NEW PASSWORD: ");
                        passDisp();
                        strcpy(rePass, encryptedPass);

                        if(strcmp(rePass, newPass)==0){
                            gotoxy(55,19); printf("PASSWORD SUCCESSFULLY CHANGED!");
                            gotoxy(55,20); system("pause");
                            strcpy(p->password, newPass);
                            saveInfoBorrower();
                            return;
                        }
                        else{
                            gotoxy(55,17); printf("NEW PASSWORD DIDN'T MATCH"); gotoxy(55,18); system("pause");
                            tries2--;
                        }
                    }
                }
                else{
                    gotoxy(55,19); printf("CURRENT PASSWORD DIDN'T MATCH\n"); gotoxy(55,20); system("pause");
                    tries1--;
                }
            }

            //If tries ay equal 0
            gotoxy(55,22); printf("YOU HAVE EXCEEDED THE MAXIMUM NUMBER OF TRIES.\n");
            system("pause");
        }

}

//The searchBook() function prompts the user to enter a search a string, and then searches the linked list for any borrower whose info matches the search string. It displays information about any matching books.
void searchBorrower(){
    BORROWER *p;
    char toSearch[51];
    int i, searchCategory;
    char* categoryPointer;

    gotoxy(30,5);printf("\033[31m ___________________________________________________________________________________________________________________");
    gotoxy(30,6);printf("|   _                                                                                                               |");
    gotoxy(30,7);printf("|  (_)                                                                                                              |");
    gotoxy(30,8);printf("|    \\                                                                                                              |");
    gotoxy(30,9);printf("|___________________________________________________________________________________________________________________|");
    printf("\033[0m");

    gotoxy(76,15);printf("SEARCH BY CATEGORY");
    gotoxy(76,16);printf("[1] Name");
    gotoxy(76,17);printf("[2] TUP ID");
    gotoxy(76,18);printf("[3] Year and Section");
    gotoxy(76,19);printf("[4] Contact Number");
    gotoxy(76,20);printf("[5] Email");
    gotoxy(38,7);printf("\033[31mENTER SEARCH CATEGORY [1-5]: ");
    gotoxy(67,7);scanf("%d", &searchCategory);

    fflush stdin;
    system("cls");

    gotoxy(30,5);printf("\033[31m ___________________________________________________________________________________________________________________");
    gotoxy(30,6);printf("|   _                                                                                                               |");
    gotoxy(30,7);printf("|  (_)  ENTER THE TEXT TO SEARCH:                                                                                   |");
    gotoxy(30,8);printf("|    \\                                                                                                              |");
    gotoxy(30,9);printf("|___________________________________________________________________________________________________________________|");
    printf("\033[0m");
    gotoxy(65,7); scanf("%[^\n]", toSearch);


    gotoxy(20,12);printf(" \033[31m_________________________ _____________________ ________________________ ____________________ _______________________________________");
    gotoxy(20,13);printf("|         NAME            |       TUP ID        |    YEAR AND SECTION    |   CONTACT NUMBER   |                EMAIL                  |");
    gotoxy(20,14);printf("|_________________________|_____________________|________________________|____________________|_______________________________________|");
    printf("\033[0m");


    p=headBorrower;
    for(i=-1; p!=NULL;){
        switch(searchCategory){ // point the pointer to the appropriate search category.
            case 1: categoryPointer= p->name; break;
            case 2: categoryPointer= p->TUP_ID; break;
            case 3: categoryPointer= p->yearSection; break;
            case 4: categoryPointer= p->contactNum; break;
            case 5: categoryPointer= p->email; break;
        }
        if(strstr(categoryPointer, toSearch)!=NULL){  // if the pointed categoryBorrowerPointer contains the substring, print the transaction.
            i++;
            gotoxy(20, 15+i); printf("%d.) ", i+1);
            gotoxy(25,15+i); printf("%s", p->name);
            gotoxy(55,15+i); printf("%s", p->TUP_ID);
            gotoxy(73,15+i); printf("%s", p->yearSection);
            gotoxy(99,15+i); printf("%s", p->contactNum);
            gotoxy(127,15+i); printf("%s", p->email);
        }
       p=p->nxt;
	}
    gotoxy(20,15+i+1); printf("\033[31m___________________________________________________________________________________________________________________________________\n");
    gotoxy(20,15+i+3); system("pause");
    printf("\033[0m");

    if (i==-1){
    gotoxy(20, 15);printf("No transactions found.");
    gotoxy(20,19); printf("\033[0m");

    }
}

//The updateBorrower() function prompts the student to enter their TUP ID., and then searches for the corresponding borrower node in the linked list. If found, it displays information about the borrower and prompts the user to choose which information to update. It then updates the chosen information if the user confirms the update.
void updateBorrower(){
BORROWER *p;
int choice,info;
char TUP_ID[14];
char update[51];
int updateInt;


    gotoxy(30,5);printf("\033[31m ___________________________________________________________________________________________________________________");
    gotoxy(30,6);printf("|   _                                                                                                               |");
    gotoxy(30,7);printf("|  (_)  ENTER YOUR TUP ID:                                                                                          |");
    gotoxy(30,8);printf("|    \\                                                                                                              |");
    gotoxy(30,9);printf("|___________________________________________________________________________________________________________________|");
    printf("\033[0m");

    gotoxy(61,7);scanf("%s", TUP_ID);
    p = locateTUP_ID(TUP_ID);

    if(p==NULL){
        printf("\nRECORD NOT FOUND!\n"); system("pause");
    }

    else{
        displayAllBorrower(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        gotoxy(49,25);printf("[1] Name");
        gotoxy(49,26);printf("[2] TUP ID");
        gotoxy(49,27);printf("[3] Year and Section");
        gotoxy(99,25);printf("[4] Contact Number");
        gotoxy(99,26);printf("[5] Email");
        gotoxy(99,27);printf("[6] Go Back");
        gotoxy(46,28); printf("________________________________________________________________________________________\n");
        gotoxy(46,29); printf("CHOOSE THE INFORMATION YOU WISH TO UPDATE (1-7): ");
        scanf("%d", &info);

        fflush stdin;
        gotoxy(55,32);system("pause");
        system("cls");

        if(info==1){
            gotoxy(30,8); printf("\033[31mCURRENT NAME: ");
            gotoxy(46,8); printf("\033[0m %s", p->name);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==2){
            gotoxy(30,8); printf("\033[31mCURRENT TUP ID: ");
            gotoxy(46,8); printf("\033[0m %s", p->TUP_ID);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==3){
            gotoxy(30,8); printf("\033[31mCURRENT YEAR AND SECTION: ");
            gotoxy(46,8); printf("\033[0m %s", p->yearSection);
            gotoxy(46,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==4){
            gotoxy(30,8); printf("\033[31mCURRENT CONTACT NUMBER: ");
            gotoxy(46,8); printf("\033[0m %s", p->contactNum);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            scanf("%[^\n]", update);
        }
        else if (info==5){
            gotoxy(30,8); printf("\033[31mCURRENT EMAIL: ");
            gotoxy(46,8); printf("\033[0m %s", p->email);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==6){
            return;
            printf("\033[0m");
        }

       gotoxy(30,12); printf("_____________________________________________________________________________________________________________________\n");
       gotoxy(30,14); printf("ARE YOU SURE TO UPDATE THE RECORD OF %s?", p->name);
       gotoxy(30,16); printf("[1] YES [2] NO : ");
       scanf("%d", &choice);
        if(choice==1){
            switch(info){
                case 1: strcpy(p->name, update); break;
                case 2: strcpy(p->TUP_ID, update); break;
                case 3: strcpy(p->yearSection, update); break;
                case 4: strcpy(p->contactNum, update); break;
                case 5: strcpy(p->email, update); break;
        }
    }
}
}

//displayAllBorrower() displays all the information of all nodes in borrower linkedlist.
void displayAllBorrower(struct borrower *p, int start, int end){
int i;

    gotoxy(15,14);printf(" \033[31m_________________________ _____________________ ________________________ ____________________ _______________________________________");
    gotoxy(15,15);printf("|         NAME            |       TUP ID        |    YEAR AND SECTION    |   CONTACT NUMBER   |                EMAIL                  |");
    gotoxy(15,16);printf("|_________________________|_____________________|________________________|____________________|_______________________________________|");
    printf("\033[0m");

    for(i=start; p!=end; i++){
         gotoxy(15, 17+i); printf("%d.) ", i+1);
         gotoxy(20,17+i); printf("%s", p->name);
         gotoxy(49,17+i); printf("%s", p->TUP_ID);
         gotoxy(71,17+i); printf("%s", p->yearSection);
         gotoxy(93,17+i); printf("%s", p->contactNum);
         gotoxy(120,17+i); printf("%s", p->email);
        p=p->nxt;
    }

    gotoxy(15,17+i+1); printf("\033[31m__________________________________________________________________________________________________________________________\n");
    gotoxy(17,17+i+3); printf("\033[0m");
    system("pause");
}

//menuBorrower() displays all the operations the admin can do on borrower records.
int menuBorrower(int choice){
    while(choice<1 || choice>5){
        system("cls");
        printf("BORROWER RECORD");
        printf("\nMENU");
        printf("\n[1] DISPLAY ALL BORROWER RECORDS");
        printf("\n[2] SEARCH BORROWING RECORD");
        printf("\n[3] UPDATE BORROWER RECORD");
        printf("\n[4] GO BACK");
        printf("\n[5] EXIT");
        printf("\nENTER OPTION: ");
        scanf("%d", &choice);
        if(choice<1 || choice>5){
            printf("\nSELECT 1-5 ONLY!\n");
            system("pause");
        }
    }
    return choice;
}

//logInAdmin() asks the admin of their password, and verifies before entering the admin portal.
void loginAdmin(){
    char defaultPass[] = "1234";
    char enteredPass[12];
    int tries= 3, flag = 0;

    while (tries > 0 && flag == 0) {
        system("cls");
        printf("\nLOG IN\n\n");
        printf("ENTER ADMIN PASSWORD: ");
        passDisp();
        strcpy(enteredPass, encryptedPass);

        if (strcmp(enteredPass, defaultPass) == 0) {
            printf("\nLOGIN SUCCESSFUL!\n");
            system("pause");
            flag = 1;
        } else {
            printf("\n\nINVALID ADMIN PASSWORD. ");
            tries--;
            printf("\nYOU HAVE %d TRIES LEFT.\n", tries);
            system("pause");
            system("cls");
        }
    }

    if (tries == 0){
        printf("YOU HAVE EXCEEDED THE MAXIMUM NUMBER OF TRIES.\n");
        system("pause");
    }
}


//encrypt() creates a copy of the original string, encrypts the copy, and returns the encrypted copy.
char* encrypt(char text[]){                     //char* - return type for string
int i=0;

    char* encrypted= malloc(strlen(text)+1);    //creates a new char pointer variable that is a copy of the text string, which can be modified without changing the original input string.
    strcpy(encrypted, text);                    //copy value of text to new string

    for(i=0; encrypted[i]!='\0'; i++){          //loop through each character of encrypted
        encrypted[i]+=29;                        //add key to each character
    }

    return encrypted;
}

//decrypt() decodes the encrypted text by subtracting the key which is 29 then it returns the text.
char* decrypt(char text[]){                //char* - return type for string
int i=0;

    for(i=0; text[i]!='\0'; i++){          //loop through each character of encrypted
        text[i]-=29;                       //subtract key to each character
    }

    return text;
}



void borrowMenu(){
char ID[7];
setFontStyle(18);
    char Menu[][50] =  {"\n\n\n\n\n\t\t\t\t\t\t\tLOGIN", "\n\n\n\n\n\t\t\t\t\t\t\tREGISTER ", "\n\n\n\n\n\t\t\t\t\t\t\tGO BACK"};
    int pointer = 0;
    const char ENTER = 13;//ASCII code for ENTER Key
    char ch = ' ';
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    while(1){

        system("cls");
        dispBorrowBooks();
        ShowConsoleCursor(0);//SET CURSOR OF


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
                        ShowConsoleCursor(1);
                        dispLogin();
                        strcpy(ID, loginBorrower());
                        borrowBook(ID);
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        getInfoBorrower();
                        addBorrower();
                        saveInfoBorrower();
                        strcpy(ID, loginBorrower());
                        borrowBook(ID);
                        break;
                    }

                    case 2:
                    {
                        ShowConsoleCursor(1);
                       return;
                    }
            }
            }
        }
    }
}


void manageBorrowerMenu(){
BORROWER *r;
setFontStyle(18);
char Menu[][50] = {"\n\n\n\n\n\t\t\t\t\t\t\tDISPLAY ALL BORROWER RECORD ", "\n\n\n\n\n\t\t\t\t\t\t\tSEARCH BORROWING RECORD ","\n\n\n\n\n\t\t\t\t\t\t\tUPDATE BORROWING RECORD","\n\n\n\n\n\t\t\t\t\t\t\tGO BACK ", "\n\n\n\n\n\t\t\t\t\t\t\tEXIT "};
int pointer = 0;
const char ENTER = 13;//ASCII code for ENTER Key
char ch = ' ';
HANDLE  hConsole;
hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while(1){
        dispManageBorrowers();
        system("cls");
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
                        //dispDisplayAllBorrower();
                        displayAllBorrower(r=headBorrower, 0, NULL);
                        break;
                    }
                    case 1:
                    {
                        ShowConsoleCursor(1);
                        //dispSearch
                        searchBorrower();
                        break;
                    }

                    case 2:
                    {
                       ShowConsoleCursor(1);
                        //dispUpdateBorrower();
                        updateBorrower(); saveInfoBorrower();
                        break;
                    }
                    case 3:
                    {
                       ShowConsoleCursor(1);
                        adminPortalMenu();
                        break;
                    }

                    case 4:
                    {
                        ShowConsoleCursor(1);
                        system("cls");
                        printf(" EXITING PROGRAM.... ");//need loading
                        system("pause");
                        exit(0);
                    }
                  }
                }
                break;
            }
        }
}
