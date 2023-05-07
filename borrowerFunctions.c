#include "borrowerFunctions.h"


//FOR BORROWER FUNCTIONS

BORROWER *locateTUP_ID(char TUP_ID[]){
BORROWER *p;

    p=headBorrower;
        while(p!=NULL && strcmp(p->TUP_ID, TUP_ID)!=0){
        p=p->nxt;
    }
    return p;
}

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

void getInfoBorrower(){
    char rePass[14];
    system("cls");
    printf("\nREGISTER\n\n");
    printf("COMPLETE THE INFORMATION BELOW\n\n");
    printf("TUP ID (Ex. 123456): TUP-M ");
    scanf("%s", &infoBorrower.TUP_ID);
    if(locateTUP_ID(infoBorrower.TUP_ID)!=NULL){
        printf("\nYOUR TUP ID IS ALREADY REGISTERED!\n"); system("pause");
    }
    else{
        PASS:
        printf("PASSWORD: ");
        passDisp();
        strcpy(infoBorrower.password, encryptedPass);
        printf("\nRE-ENTER PASSWORD: ");
        passDisp();
        strcpy(rePass, encryptedPass);
        if(strcmp(rePass, infoBorrower.password)==0){
                printf("\nNAME (EX. JUAN A. DELA CRUZ): ");
                fflush stdin;
                scanf("%[^\n]", &infoBorrower.name);
                fflush stdin;
                printf("COURSE AND SECTION (EX: BSCS-NS2A): ");
                scanf("%s", &infoBorrower.yearSection);
                printf("CONTACT NUMBER (Ex. 09123456789): ");
                scanf("%s", &infoBorrower.contactNum);
                printf("EMAIL ADDRESS (Ex. juandelacruz@tup.edu.ph): ");
                scanf("%s", &infoBorrower.email);
                printf("\nYOUR ACCOUNT IS SUCCESSFULLY REGISTERED!\n");
                system("pause");
                return;
        }
        else{
            printf("\nPASSWORD DIDN'T MATCH\n");
            system("pause"); system("cls");
            goto PASS;
        }
    }
}

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
            fprintf(fp, "%s\n%s %s %s %s %s\n\n", p->name, p->TUP_ID, p->password, p->yearSection, p->contactNum, p->email);
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
           // strcpy(infoBorrower.TUP_ID, decrypt(infoBorrower.TUP_ID)); strcpy(infoBorrower.password, decrypt(infoBorrower.password)); strcpy(infoBorrower.yearSection, decrypt(infoBorrower.yearSection));
            //strcpy(infoBorrower.contactNum, decrypt(infoBorrower.email)); strcpy(infoBorrower.name, decrypt(infoBorrower.name));

            if(!feof(fp)){
                addBorrower();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

BORROWER* loginBorrower(){
BORROWER *p;
char enteredID[7], enteredPass[7];
int tries=3, flag=0;

    while (tries > 0 && flag==0) {
        system("cls");
        printf("\nLOG IN\n\n");
        printf("TUP ID (Ex. 123456): TUP-M ");
        scanf("%s", enteredID);
        printf("PASSWORD: ");
        passDisp();
        strcpy(enteredPass, encryptedPass);

        p=locateTUP_ID(enteredID);
        if(p!=NULL && strcmp(enteredPass, p->password)==0){     //para di need i-compare lahat ng pass, ID lang.
            printf("\nLOGIN SUCCESSFUL!\n"); system("pause");
            flag=1;
            return p->TUP_ID;
        }

        else{
            printf("\nINVALID TUP ID OR PASSWORD. ");
            tries--;
            printf("\nYOU HAVE %d TRIES LEFT.\n", tries);
            system("pause");
            system("cls");
        }
    }
    if (tries == 0) {
        printf("YOU HAVE EXCEEDED THE MAXIMUM NUMBER OF TRIES.\n");
        system("pause");
    }
}

void changePassBorrower(){
BORROWER *p;
char currPass[14], newPass[14], rePass[14], TUP_ID[7];
int tries1=3, tries2=3, flag1=0, flag2=0;

        printf("\nEnter your TUP ID: TUP-M ");
        scanf("%s", TUP_ID);
        p=locateTUP_ID(TUP_ID);
        if(p==NULL){
            printf("\nYOU ARE NOT REGISTERED! GO TO BORROW OPTION TO REGISTER.\n"); system("pause");
        }

        else{
            //FOR CURRENT PASS
            while(tries1>0 && flag1==0){
                system("cls");
                printf("\nENTER CURRENT PASSWORD: ");
                passDisp();
                if(strcmp(encryptedPass, p->password)==0){
                    flag1=1;

                    //FOR NEW PASS
                    while(tries2 && flag2==0){
                        system("cls");
                        printf("\nENTER NEW PASSWORD: ");
                        passDisp();
                        strcpy(newPass, encryptedPass);
                        printf("\nRE-ENTER NEW PASSWORD: ");
                        passDisp();
                        strcpy(rePass, encryptedPass);

                        if(strcmp(rePass, newPass)==0){
                            printf("\nPASSWORD SUCCESSFULLY CHANGED!\n");
                            system("pause");
                            strcpy(p->password, newPass);
                            saveInfoBorrower();
                            return;
                        }
                        else{
                            printf("\nNEW PASSWORD DIDN'T MATCH\n"); system("pause");
                            tries2--;
                        }
                    }
                }
                else{
                    printf("\nCURRENT PASSWORD DIDN'T MATCH\n"); system("pause");
                    tries1--;
                }
            }

            //If tries ay equal 0
            printf("\nYOU HAVE EXCEEDED THE MAXIMUM NUMBER OF TRIES.\n");
            system("pause");
        }

}

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
