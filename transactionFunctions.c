#include "transactionFunctions.h"


int menuTransaction(int choice){
    while(choice<1 || choice>4){
        system("cls");
        printf("TRANSACTION RECORD");
        printf("\nMENU");
        printf("\n[1] EDIT STATUS");
        printf("\n[2] SEARCH BORROWING RECORD");
        printf("\n[3] DISPLAY ALL BORROWING RECORD");
        printf("\n[4] GO BACK");
        printf("\nENTER OPTION: ");
        scanf("%d", &choice);
        if(choice<1 || choice>4){
            printf("\nSELECT 1-4 ONLY!\n");
            system("pause");
        }
    }
    return choice;
}

void borrowBook(char ID[7]){
BOOK *pBook;
BORROWER *pBorrower;
TRANSACTION *pTransaction;
char enteredBookRef[14];
int ch;

    pBorrower=locateTUP_ID(ID);
    pTransaction=headTransaction;

    system("cls");
    printf("\nWELCOME, %s\n", pBorrower->name);
    printf("\nENTER BOOK REFERENCE NO. : ");
    scanf("%s", enteredBookRef);

    pBook= locateBook(enteredBookRef);

    if(pBook==NULL){
       printf("\nSELECTED BOOK IS NOT AVAILABLE\n"); system("pause");
    }

    else if(pBook->totalStock - pBook->borrower <=0){
        printf("\nSELECTED BOOK IS OUT OF STOCK!\n"); system("pause");
    }

    else{
        system("cls");
        displayBook(pBook,0,pBook->nxt);
        system("cls");
        printf("\nBOOK REFERENCE NO.: %s", pBook->refNum);
        printf("\nBOOK TO BORROW: %s", pBook->title);
        strcpy(infoTransaction.title, pBook->title);
        printf("\nBOOK AUTHOR: %s", pBook->author);
        strcpy(infoTransaction.author, pBook->author);
        printf("\n\nBORROWER'S NAME: %s", pBorrower->name);
        strcpy(infoTransaction.borrower, pBorrower->name);
        printf("\nTUP ID NO.: %s", pBorrower->TUP_ID);
        strcpy(infoTransaction.TUP_ID, pBorrower->TUP_ID);
        strcpy(infoTransaction.refNum, pBook->refNum);
        printf("\nENTER DATE BORROWED [MM/DD/YY]: ");
        scanf("%s", infoTransaction.dateBorrowed);
        printf("ENTER DATE TO RETURN [MM/DD/YY]: ");
        scanf("%s", infoTransaction.dateToReturn);
        strcpy(infoTransaction.librarian, "MS. LAICA YGOT");
        printf("LIBRARIAN IN CHARGE: MS. LAICA YGOT");
        strcpy(infoTransaction.status, "TO RETURN");
        printf("\nDO YOU WANT TO PROCEED WITH THE TRANSACTION?\n[1] YES [2] NO\n");
        printf("SELECT OPTION (1-2): ");
        fflush stdin;
        scanf("%d", &ch);
        if(ch==1){
            addTransaction();
            pBook->borrower+=1;
            saveTransaction();
            saveBook();
        }
        else{
            return;
        }

    }
}

int addTransaction(){
TRANSACTION *q, *p, *n;

    n= (TRANSACTION*) malloc(sizeof(TRANSACTION));    //allocates memory to n.
    *n= infoTransaction;                           //copy info of the book to n.

    p=q=headTransaction;                           //point all pointers to head.
    while(p!=NULL){
        q=p;
        p=p->nxt;
    }

    if(p==headTransaction){    //if to insert at the head.
        headTransaction=n;
    }
    else{           //if to insert in between or at the end.
        q->nxt=n;
    }
    n->nxt=p;  //insert p at the end which contains next node or NULL.
}

void searchTransaction(){
    TRANSACTION *p;
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
    gotoxy(76,16);printf("[1] Book Title");
    gotoxy(76,17);printf("[2] Author");
    gotoxy(76,18);printf("[3] Reference Number");
    gotoxy(76,19);printf("[4] Borrower");
    gotoxy(76,20);printf("[5] TUP ID");
    gotoxy(76,21);printf("[6] Date Borrowed");
    gotoxy(76,22);printf("[7] Date Return");
    gotoxy(76,23);printf("[8] Librarian In-Charged");
    gotoxy(76,24);printf("[9] Status");
    gotoxy(38,7);printf("\033[31mENTER SEARCH CATEGORY [1-9]: ");
    scanf("%d", &searchCategory);

    fflush stdin;
    system("cls");

    gotoxy(30,5);printf("\033[31m ___________________________________________________________________________________________________________________");
    gotoxy(30,6);printf("|   _                                                                                                               |");
    gotoxy(30,7);printf("|  (_)  ENTER THE TEXT TO SEARCH:                                                                                   |");
    gotoxy(30,8);printf("|    \\                                                                                                              |");
    gotoxy(30,9);printf("|___________________________________________________________________________________________________________________|");
    printf("\033[0m");
    gotoxy(65,7); scanf("%[^\n]", toSearch);

    gotoxy(2,12);printf("\033[31m _________________________ _____________________ __________________ __________________ ____________ _______________ ________________ ______________ ____________");
    gotoxy(2,13);printf("|         TITLE           |       AUTHOR        | REFERENCE NUMBER |     BORROWER     |   TUP ID   | DATE BORROWED | DATE TO RETURN |  LIBRARIAN   |   STATUS   |");
    gotoxy(2,14);printf("|_________________________|_____________________|__________________|__________________|____________|_______________|________________|______________|____________|");
    printf("\033[0m");


    p=headTransaction;
    for(i=-1; p!=NULL;){
        switch(searchCategory){ // point the pointer to the appropriate search category.
            case 1: categoryPointer= p->title; break;
            case 2: categoryPointer= p->author; break;
            case 3: categoryPointer= p->refNum; break;
            case 4: categoryPointer= p->borrower; break;
            case 5: categoryPointer= p->TUP_ID; break;
            case 6: categoryPointer= p->dateBorrowed; break;
            case 7: categoryPointer= p->dateToReturn; break;
            case 8: categoryPointer= p->librarian; break;
            case 9: categoryPointer= p->status; break;
        }
        if(strstr(categoryPointer, toSearch)!=NULL){  // if the pointed categoryBorrowerPointer contains the substring, print the transaction.
            i++;
              gotoxy(3, 15+i); printf("%d.) ", i+1);
              gotoxy(8,15+i); printf("%s", p->title);
              gotoxy(32,15+i);; printf("%s", p->author);
              gotoxy(54,15+i); printf("%s", p->refNum);
              gotoxy(74,15+i); printf("%s", p->borrower);
              gotoxy(93,15+i); printf("%s", p->TUP_ID);
              gotoxy(107,15+i); printf("%s", p->dateBorrowed);
              gotoxy(122,15+i); printf("%s", p->dateToReturn);
              gotoxy(138,15+i); printf("%s", p->librarian);
              gotoxy(152,15+i); printf("%s", p->status);
        }
        p=p->nxt;
	}
	   gotoxy(2,15+i+1); printf("\033[31m__________________________________________________________________________________________________________________________________________________________\n");
    gotoxy(2,15+i+3); system("pause");
    printf("\033[0m");

    if (i==-1){
    gotoxy(2,12);printf("No transactions found.\n");
    gotoxy(2,12);printf("\033[0m");
    system("pause");
    }
}

void displayAllTransaction(struct transaction *p, int start, int end){
int i;

    gotoxy(2,5);printf("\033[31m _________________________ _____________________ __________________ __________________ ____________ _______________ ________________ ______________ ____________");
    gotoxy(2,6);printf("|         TITLE           |       AUTHOR        | REFERENCE NUMBER |     BORROWER     |   TUP ID   | DATE BORROWED | DATE TO RETURN |  LIBRARIAN   |   STATUS   |");
    gotoxy(2,7);printf("|_________________________|_____________________|__________________|__________________|____________|_______________|________________|______________|____________|");
    printf("\033[0m");

    for(i=start; p!=end; i++){
        gotoxy(3, 8+i); printf("%d.) ", i+1);
        gotoxy(8,8+i); printf("%s", p->title);
        gotoxy(32,8+i);; printf("%s", p->author);
        gotoxy(54,8+i); printf("%s", p->refNum);
        gotoxy(74,8+i); printf("%s", p->borrower);
        gotoxy(93,8+i); printf("%s", p->TUP_ID);
        gotoxy(107,8+i); printf("%s", p->dateBorrowed);
        gotoxy(122,8+i); printf("%s", p->dateToReturn);
        gotoxy(138,8+i); printf("%s", p->librarian);
        gotoxy(152,8+i); printf("%s", p->status);

        p=p->nxt;
    }
    gotoxy(3,8+i+1); printf("\033[31m____________________________________________________________________________________________________________________________________________________\n");
    gotoxy(5,8+i+3); system("pause");
    printf("\033[0m");

}

void saveTransaction(){
FILE *fp= fopen("transactionDetails.txt", "w+");
TRANSACTION *p;

    if(fp==NULL){
        printf("\nTHE FILE ""transactionDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        p=headTransaction;
        while(p!=NULL){
            fprintf(fp, "%s\n%s\n%s\n%s\n%s %s %s %s\n%s\n\n", p->title, p->author, p->refNum, p->borrower, p->TUP_ID, p->dateBorrowed, p->dateToReturn, p->librarian, p->status);
            p=p->nxt;
        }
        fclose(fp);
    }
}

void retrieveTransaction(){
FILE *fp= fopen("transactionDetails.txt", "r+");
TRANSACTION *p;

    if(fp==NULL){
        printf("THE FILE ""transactionDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        while(1){
            fscanf(fp, "\n%[^\n]\n", &infoTransaction.title);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoTransaction.author);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoTransaction.refNum);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoTransaction.borrower);
            fflush stdin;
            fscanf(fp, "%s %s %s %s\n", infoTransaction.TUP_ID, infoTransaction.dateBorrowed, infoTransaction.dateToReturn, infoTransaction.librarian);
            fscanf(fp, "%[^\n]", &infoTransaction.status);
            //decrypting the retrieved info.
            //strcpy(info.title, decrypt(info.title)); strcpy(info.author, decrypt(info.author)); strcpy(info.category, decrypt(info.category));
            //strcpy(info.year, decrypt(info.year)); strcpy(info.ISBN, decrypt(info.ISBN));

            if(!feof(fp)){
                addTransaction();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

//The locate() function searches for the book node with a given ISBN, and returns a pointer to that node if it is found.
struct transaction *locateTransaction(char TUP_ID[], char refNum[]){
TRANSACTION *p;

    p=headTransaction;
    while(p!=NULL){
        if(strcmp(TUP_ID, p->TUP_ID)==0 && strcmp(refNum, p->refNum)==0){
            return p;
        }
    p=p->nxt;
    }

    return p;

}

void editStatus(){
BOOK *pBook;
TRANSACTION *pTransac;
char enteredID[7], enteredReference[14], returned[10]="RETURNED";

    printf("TUP ID (Ex. 123456): TUP-M ");
    scanf("%s", enteredID);
    printf("ENTER REFERENCE NUMBER: ");
    scanf("%s", enteredReference);
    pTransac=locateTransaction(enteredID, enteredReference);
    if(pTransac==NULL){
        printf("\nTRANSACTION RECORD NOT FOUND!\n"); system("pause");
    }

    else{
        fflush stdin;
        strcpy(pTransac->status, returned);
        printf("%s", pTransac->status);
        pBook=locateBook(enteredReference);
        pBook->borrower-=1;
        printf("\nRECORD SUCCESSFULLY EDITED\n"); system("pause");
    }
}
