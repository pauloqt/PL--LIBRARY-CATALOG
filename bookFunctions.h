#ifndef BOOKFUNCTIONS_H_INCLUDED
#define BOOKFUNCTIONS_H_INCLUDED

typedef struct book{
    char title[51], author[51], year[5], refNum[14], material[16], category[31];
    int shelfNo, totalStock, borrower, currentStock;
    struct book *nxt;
}BOOK;

BOOK *headBook, infoBook;   //declaring head node and info struct variable where to store the initial info before storing in linked list.

void getInfoBook();
int addBook();
struct book *locateBook(char refNum[]);
void updateBook();
void delBook();
void searchBook();
void displayBook(struct book *p, int start, int end);
void saveBook();
void retrieveBook();
char* encryptBook(char text[]);
char* decryptBook(char text[]);
int menuBook(int choice);

#endif // BOOKFUNCTIONS_H_INCLUDED
