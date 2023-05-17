#ifndef TRANSACTIONFUNCTIONS_H_INCLUDED
#define TRANSACTIONFUNCTIONS_H_INCLUDED

//Struct TRANSACTION containing attributes of the transaction
typedef struct transaction{
    char title[51], author[31], refNum[14], borrower[31], TUP_ID[7];
    char dateBorrowed[11], dateToReturn[11], librarian[31], status[12];
    struct transaction *nxt;
}TRANSACTION;

TRANSACTION *headTransaction, infoTransaction;

int menuTransaction(int choice);
void borrowBook(char ID[7]);
int addTransaction();
void searchTransaction();
void displayAllTransaction(struct transaction *p, int start, int end);
void saveTransaction();
void retrieveTransaction();
void editStatus();
struct transaction *locateTransaction(char TUP_ID[], char refNum[]);

#endif // TRANSACTIONFUNCTIONS_H_INCLUDED
