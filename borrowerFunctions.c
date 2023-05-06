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
            system("cls");
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
