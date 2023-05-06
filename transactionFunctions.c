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
        printf("LIBRARIAN IN CHARGE: ");
        scanf("%s", infoTransaction.librarian);
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

    printf("\nSEARCH BY CATEGORY");
    printf("\n[1] Book Title");
    printf("\n[2] Author");
    printf("\n[3] Reference Number");
    printf("\n[4] Borrower");
    printf("\n[5] TUP ID");
    printf("\n[6] Date Borrowed");
    printf("\n[7] Date Return");
    printf("\n[8] Librarian In-Charged");
    printf("\n[9] Status");
    printf("\nENTER SEARCH CATEGORY [1-8]: ");
    scanf("%d", &searchCategory);

    fflush stdin;
    printf("ENTER THE TEXT TO SEARCH: ");
    scanf("%[^\n]", toSearch);

    system("cls");
    gotoxy(10,3); printf("TITLE"); gotoxy(30,3); printf("AUTHOR"); gotoxy(50,3); printf("REFERENCE NUMBER");
    gotoxy(70,3); printf("BORROWER");gotoxy(90,3); printf("TUP ID");  gotoxy(100,3); printf("DATE BORROWED");
    gotoxy(115,3); printf("DATE TO RETURN");gotoxy(130,3); printf("LIBRARIAN"); gotoxy(150,3); printf("STATUS");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");

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
            gotoxy(5, 6+i); printf("%d.) ", i+1);
            gotoxy(10,6+i); printf("%s", p->title);
            gotoxy(30,6+i); printf("%s", p->author);
            gotoxy(50,6+i); printf("%s", p->refNum);
            gotoxy(70,6+i); printf("%s", p->borrower);
            gotoxy(90,6+i); printf("%s", p->TUP_ID);
            gotoxy(100,6+i); printf("%s", p->dateBorrowed);
            gotoxy(115,6+i); printf("%s", p->dateToReturn);
            gotoxy(130,6+i); printf("%s", p->librarian);
            gotoxy(150,6+i); printf("%s", p->status);
        }
		p=p->nxt;
	}
	gotoxy(5,10+i+1); printf("_______________________________________________________________________________________________________________________________________\n");
    gotoxy(5,10+i+3);

    if (i==-1) printf("\nNo transactions found.\n");
    system("pause");
}

void displayAllTransaction(struct transaction *p, int start, int end){
int i;

    gotoxy(10,3); printf("TITLE"); gotoxy(30,3); printf("AUTHOR"); gotoxy(50,3); printf("REFERENCE NUMBER");
    gotoxy(70,3); printf("BORROWER");gotoxy(90,3); printf("TUP ID");  gotoxy(100,3); printf("DATE BORROWED");
    gotoxy(115,3); printf("DATE TO RETURN");gotoxy(130,3); printf("LIBRARIAN"); gotoxy(150,3); printf("STATUS");
    gotoxy(5,5); printf("_______________________________________________________________________________________________________________________________________________\n");

    for(i=start; p!=end; i++){
        gotoxy(5, 6+i); printf("%d.) ", i+1);
        gotoxy(10,6+i); printf("%s", p->title);
        gotoxy(30,6+i); printf("%s", p->author);
        gotoxy(50,6+i); printf("%s", p->refNum);
        gotoxy(70,6+i); printf("%s", p->borrower);
        gotoxy(90,6+i); printf("%s", p->TUP_ID);
        gotoxy(100,6+i); printf("%s", p->dateBorrowed);
        gotoxy(115,6+i); printf("%s", p->dateToReturn);
        gotoxy(130,6+i); printf("%s", p->librarian);
        gotoxy(150,6+i); printf("%s", p->status);

        p=p->nxt;
    }

    gotoxy(5,6+i+1); printf("_______________________________________________________________________________________________________________________________________________\n");
    gotoxy(5,6+i+3); system("pause");
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
    while(p!=NULL && strcmp(refNum, p->refNum)!=0 && strcmp(TUP_ID, p->TUP_ID)!=0 ){
        p=p->nxt;
    }

    return p;
}

void editStatus(){
BOOK *pBook;
TRANSACTION *pTransac;
char enteredID[7], enteredReference[14], returned[10]="RETURNED";

    pTransac=headTransaction;
    printf("TUP ID (Ex. 123456): TUP-M ");
    scanf("%s", enteredID);
    printf("ENTER REFERENCE NUMBER: ");
    scanf("%s", enteredReference);
    pTransac=locateTransaction(enteredID, enteredReference);
    if(pTransac==NULL){
        printf("\nTRANSACTION RECORD NOT FOUND!\n"); system("pause");
    }

    else{
        strcpy(pTransac->status, returned);
        pBook=locateBook(enteredReference);
        pBook->borrower-=1;
        printf("\nRECORD SUCCESSFULLY EDITED\n"); system("pause");
    }
}
