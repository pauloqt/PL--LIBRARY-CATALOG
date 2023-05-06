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
    system("cls");
    printf("\nREGISTER\n\n");
    printf("COMPLETE THE INFORMATION BELOW\n\n");
    printf("TUP ID (Ex. 123456): TUP-M ");
    scanf("%s", &infoBorrower.TUP_ID);
    if(locateTUP_ID(infoBorrower.TUP_ID)!=NULL){
        printf("\nYOUR TUP ID IS ALREADY REGISTERED!\n"); system("pause");
    }
    else{
        printf("PASSWORD: ");
        passDisp();
        strcpy(infoBorrower.password, encryptedPass);
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
            //decrypting the retrieved info.
            //strcpy(info.title, decrypt(info.title)); strcpy(info.author, decrypt(info.author)); strcpy(info.category, decrypt(info.category));
            //strcpy(info.year, decrypt(info.year)); strcpy(info.ISBN, decrypt(info.ISBN));

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

    printf("\nSEARCH BY CATEGORY");
    printf("\n[1] Name");
    printf("\n[2] TUP ID");
    printf("\n[3] Year and Section");
    printf("\n[4] Contact Number");
    printf("\n[5] Email");
    printf("\nENTER SEARCH CATEGORY [1-5]: ");
    scanf("%d", &searchCategory);


    fflush stdin;
    printf("ENTER THE TEXT TO SEARCH: ");
    scanf("%[^\n]", toSearch);

    system("cls");
    gotoxy(10,3); printf("NAME"); gotoxy(30,3); printf("TUP ID"); gotoxy(50,3); printf("YEAR AND SECTION");
    gotoxy(70,3); printf("CONTACT NUMBER");gotoxy(100,3); printf("EMAIL");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");


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
            gotoxy(5, 6+i); printf("%d.) ", i+1);
            gotoxy(10,6+i); printf("%s", p->name);
            gotoxy(30,6+i); printf("%s", p->TUP_ID);
            gotoxy(50,6+i); printf("%s", p->yearSection);
            gotoxy(70,6+i); printf("%s", p->contactNum);
            gotoxy(100,6+i); printf("%s", p->email);
        }
		p=p->nxt;
	}
	gotoxy(5,10+i+1); printf("_______________________________________________________________________________________________________________________________________\n");
    gotoxy(5,10+i+3);

    if (i==-1) printf("\nNo transactions found.\n");
    system("pause");
}

void updateBorrower(){
BORROWER *p;
int choice,info;
char TUP_ID[14];
char update[51];
int updateInt;

    printf("ENTER YOUR TUP ID: ");
    scanf("%s", TUP_ID);
    p = locateTUP_ID(TUP_ID);

    if(p==NULL){
        printf("\nRECORD NOT FOUND!\n"); system("pause");
    }

    else{
        displayAllBorrower(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        printf("\n[1] Name");
        printf("\n[2] TUP ID");
        printf("\n[3] Year and Section");
        printf("\n[4] Contact Number");
        printf("\n[5] Email");
        printf("\nCHOOSE THE INFORMATION YOU WISH TO UPDATE (1-5): ");
        scanf("%d", &info);
        fflush stdin;
        printf("\nENTER THE UPDATED INFORMATION: ");
        scanf("%[^\n]", update);}

        printf("\nARE YOU SURE TO UPDATE THE RECORD OF %s?\n[1]YES [2]NO : ", p->name);
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

void displayAllBorrower(struct borrower *p, int start, int end){
int i;

    gotoxy(10,3); printf("NAME"); gotoxy(30,3); printf("TUP ID"); gotoxy(50,3); printf("YEAR AND SECTION");
    gotoxy(70,3); printf("CONTACT NUMBER");gotoxy(100,3); printf("EMAIL");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");

    for(i=start; p!=end; i++){
         gotoxy(5, 6+i); printf("%d.) ", i+1);
            gotoxy(10,6+i); printf("%s", p->name);
            gotoxy(30,6+i); printf("%s", p->TUP_ID);
            gotoxy(50,6+i); printf("%s", p->yearSection);
            gotoxy(70,6+i); printf("%s", p->contactNum);
            gotoxy(100,6+i); printf("%s", p->email);

        p=p->nxt;
    }

    gotoxy(5,6+i+1); printf("_______________________________________________________________________________________________________________________________________________\n");
    gotoxy(5,6+i+3); system("pause");
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
