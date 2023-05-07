#include "bookFunctions.h"

//BOOK FUNCTIONS
//The getInfo() function prompts the user to enter information about a book, including its title, author, year published, ISBN, category, total number of stock, and number of borrowers. It stores this information in the info struct variable.

void getInfoBook(){
    fflush stdin;
    printf("ENTER BOOK TITLE: ");
    scanf("%[^\n]", infoBook.title);
    fflush stdin;
    printf("ENTER AUTHOR: ");
    scanf("%[^\n]", infoBook.author);
    fflush stdin;
    printf("ENTER YEAR PUBLISHED: ");
    scanf("%s", infoBook.year);
    printf("ENTER REFERENCE NUMBER: ");
    scanf("%s", infoBook.refNum);
    printf("ENTER MATERIAL: ");
    scanf("%s", infoBook.material);
    fflush stdin;
    printf("ENTER BOOK CATEGORY: ");
    scanf("%[^\n]", infoBook.category);
    printf("ENTER SHELF NO.: ");
    scanf("%d", &infoBook.shelfNo);
    printf("ENTER TOTAL NO. STOCK: ");
    scanf("%d", &infoBook.totalStock);
    printf("ENTER TOTAL NO. OF BORROWER: ");
    scanf("%d", &infoBook.borrower);
}


//The add() function adds a new node to the linked list in alphabetical order, with the info struct as its data.
int addBook(){
BOOK *q, *p, *n;

    n= (BOOK*) malloc(sizeof(BOOK));    //allocates memory to n.
    *n= infoBook;                           //copy info of the book to n.

    p=q=headBook;                           //point all pointers to head.
    while(p!=NULL && strcmp(infoBook.title, p->title)>=0){
        q=p;
        p=p->nxt;
    }

    if(p==headBook){    //if to insert at the head.
        headBook=n;
    }
    else{           //if to insert in between or at the end.
        q->nxt=n;
    }

    n->nxt=p;  //insert p at the end which contains next node or NULL.
}

//The locate() function searches for the book node with a given ISBN, and returns a pointer to that node if it is found.
struct book *locateBook(char refNum[]){
BOOK *p;

    p=headBook;
    while(p!=NULL && strcmp(refNum, p->refNum)!=0){
        p=p->nxt;
    }

    return p;
}

//The update() function prompts the user to enter an ISBN, and then searches for the corresponding book node in the linked list. If found, it displays information about the book and prompts the user to choose which information to update. It then updates the chosen information if the user confirms the update.
void updateBook() {
BOOK *p;
int choice,info;
char refNum[14];
char update[51];
int updateInt;

    gotoxy(30,5);printf("\033[31m ___________________________________________________________________________________________________________________");
    gotoxy(30,6);printf("|   _                                                                                                               |");
    gotoxy(30,7);printf("|  (_)  ENTER REFERENCE NUMBER OF THE BOOK:                                                                         |");
    gotoxy(30,8);printf("|    \\                                                                                                              |");
    gotoxy(30,9);printf("|___________________________________________________________________________________________________________________|");
    printf("\033[0m");
    gotoxy(74,7);  scanf("%s", refNum);

    p = locateBook(refNum);
    if(p==NULL){
        gotoxy(74,11); printf("RECORD NOT FOUND!"); system("pause");
    }
    else{
        displayBook(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        gotoxy(41,25); printf("[1] BOOK TITLE");
        gotoxy(41,26); printf("[2] AUTHOR");
        gotoxy(41,27); printf("[3] YEAR PUBLISHED");
        gotoxy(82,25); printf("[4] BOOK REFERENCE NUMBER");
        gotoxy(82,26); printf("[5] MATERIAL");
        gotoxy(82,27); printf("[6] CATEGORY");
        gotoxy(116,25); printf("[7] SHELF NO.");
        gotoxy(116,26); printf("[8] TOTAL STOCK");
        gotoxy(116,27); printf("[9] NO. OF BORROWER");
        gotoxy(30,28); printf("_____________________________________________________________________________________________________________________\n");
        gotoxy(30,29); printf("CHOOSE THE INFORMATION YOU WISH TO UPDATE (1-7): ");
        scanf("%d", &info);
        fflush stdin;

        gotoxy(55,32);system("pause");

        system("cls");

       if(info==1){
            gotoxy(30,8); printf("\033[31mCURRENT TITLE: ");
            gotoxy(46,8); printf("\033[0m %s", p->title);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==2){
            gotoxy(30,8); printf("\033[31mCURRENT AUTHOR: ");
            gotoxy(46,8); printf("\033[0m %s", p->author);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==3){
            gotoxy(30,8); printf("\033[31mCURRENT YEAR PUBLISHED: ");
            gotoxy(46,8); printf("\033[0m %s", p->year);
            gotoxy(46,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==4){
            gotoxy(76,8); printf("\033[31mCURRENT BOOK REFERENCE: ");
            gotoxy(46,8); printf("\033[0m %s", p->refNum);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            scanf("%[^\n]", update);
        }
        else if (info==5){
            gotoxy(30,8); printf("\033[31mCURRENT MATERIAL: ");
            gotoxy(46,8); printf("\033[0m %s", p->material);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==6){
            gotoxy(30,8); printf("\033[31mCURRENT CATEGORY: ");
            gotoxy(46,8); printf("\033[0m %s", p->category);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%[^\n]", update);
        }
        else if (info==7){
            gotoxy(30,8); printf("\033[31mCURRENT SHELF NO.:");
            gotoxy(46,8); printf("\033[0m %d", p->shelfNo);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%d", &updateInt);
        }
        else if (info==8){
            gotoxy(30,8); printf("\033[31mCURRENT STOCK: ");
            gotoxy(46,8); printf("\033[0m %d", p->currentStock);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%d", &updateInt);
        }
        else if (info==9){
            gotoxy(30,8); printf("\033[31mCURRENT NO. BORROWER: ");
            gotoxy(46,8); printf("\033[0m %d", p->borrower);
            gotoxy(30,10); printf("\033[31mENTER THE UPDATED INFORMATION: ");
            printf("\033[0m");scanf("%d", &updateInt);
        }

        /*
        if(info==7 || info==8 || info==9)
            scanf("%d", &updateInt);
        else{scanf("%[^\n]", update);}*/

        gotoxy(30,12); printf("_____________________________________________________________________________________________________________________\n");
        gotoxy(30,14); printf("ARE YOU SURE TO UPDATE THE RECORD OF %s?", p->title);
        gotoxy(30,16); printf("[1] YES [2] NO : ");
        scanf("%d", &choice);
        if(choice==1){
            switch(info){
                case 1: strcpy(p->title, update); break;
                case 2: strcpy(p->author, update); break;
                case 3: strcpy(p->year, update); break;
                case 4: strcpy(p->refNum, update); break;
                case 5: strcpy(p->material, update); break;
                case 6: strcpy(p->category, update); break;
                case 7: p->shelfNo= updateInt; break;
                case 8: p->totalStock= updateInt; break;
                case 9: p->borrower= updateInt; break;
            }
        }
    }
}

//The del() function prompts the user to enter an ISBN, and then searches for the corresponding book node in the linked list. If found, it removes the node from the linked list.
void delBook(){
BOOK *p, *q;
int choice;
char refNum[14];

    printf("ENTER THE REFERENCE NUMBER OF THE BOOK: ");
    scanf("%s", refNum);
    p=headBook;
    while(p!=NULL && strcmp(refNum, p->refNum)!=0){
        q=p;
        p=p->nxt;
    }

    if(p==NULL){
        printf("\nRECORD NOT FOUND!\n"); system("pause");
    }

    else{
        displayBook(p, 0, p->nxt);  //display(exact position, start sa 1, end if != p->nxt)
        printf("\nARE YOU SURE TO DELETE THE RECORD OF %s?\n[1]YES [2]NO : ", p->title);
        fflush stdin;
        scanf("%d", &choice);
        if(choice==1){
            if(p==headBook){
                headBook=p->nxt;
            }

            else{
                q->nxt=p->nxt;
            }
            printf("\n_______________________________________________________");
            printf("\nTHE RECORD OF %s DELETED SUCCESSFULLY.\n", p->title); system("pause");
            free(p);
        }
    }
}

//The search() function prompts the user to enter a search term, and then searches the linked list for any books whose title, author, or category matches the search term. It displays information about any matching books.
void searchBook(){
BOOK *p;
char toSearch[51];
char text[51];
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
    gotoxy(76,18);printf("[3] Year Published");
    gotoxy(76,19);printf("[4] Material");
    gotoxy(76,20);printf("[5] Topic Category");
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


    gotoxy(3,12);printf("\033[31m _________________________ _____________________ ________ __________________ ______________ ________________ __________ _____________ __________ _______________");
    gotoxy(3,13);printf("|         TITLE           |       AUTHOR        |  YEAR  | REFERENCE NUMBER |   MATERIAL   |    CATEGORY    | SHELF NO.| TOTAL STOCK | BORROWER | CURRENT STOCK |");
    gotoxy(3,14);printf("|_________________________|_____________________|________|__________________|______________|________________|__________|_____________|__________|_______________|");
    printf("\033[0m");

    p=headBook;
    for(i=-1; p!=NULL;){
        switch(searchCategory){ //ipo-point si pointer kung saang search category.
        case 1: categoryPointer= p->title; break;
        case 2: categoryPointer= p->author; break;
        case 3: categoryPointer= p->year; break;
        case 4: categoryPointer= p->material; break;
        case 5: categoryPointer= p->category; break;
        }

        if(strstr(categoryPointer, toSearch)!=NULL){  //if ang pino-point ni categoryPointer ay may ganitong "substring", print, else next.
            i++;
              gotoxy(3,15+i); printf("%d.) ", i+1);
              gotoxy(8,15+i); printf("%s", p->title);
              gotoxy(32,15+i); printf("%s", p->author);
              gotoxy(54,15+i); printf("%s", p->year);
              gotoxy(63,15+i); printf("%s", p->refNum);
              gotoxy(82,15+i); printf("%s", p->material);
              gotoxy(97,15+i); printf("%s", p->category);
              gotoxy(116,15+i); printf("%d", p->shelfNo);
              gotoxy(130,15+i); printf("%d", p->totalStock);
              gotoxy(141,15+i); printf("%d", p->borrower);
              gotoxy(155,15+i); printf("%d", p->totalStock-p->borrower);
        }
        p=p->nxt;
    }
    gotoxy(3,15+i+1); printf("\033[31m_____________________________________________________________________________________________________________________________________________________\n");
    printf("\033[0m");
    gotoxy(25,15+i+3);system("pause");
}

//The display() function displays information about all the books in the linked list.
void displayBook(struct book *p, int start, int end){
int i;
    gotoxy(3,14);printf("\033[31m _________________________ _____________________ ________ __________________ ______________ ________________ __________ _____________ __________ _______________");
    gotoxy(3,15);printf("|         TITLE           |       AUTHOR        |  YEAR  | REFERENCE NUMBER |   MATERIAL   |    CATEGORY    | SHELF NO.| TOTAL STOCK | BORROWER | CURRENT STOCK |");
    gotoxy(3,16);printf("|_________________________|_____________________|________|__________________|______________|________________|__________|_____________|__________|_______________|");
    printf("\033[0m");

    for(i=start; p!=end; i++){
        gotoxy(3,17+i); printf("%d.) ", i+1);
        gotoxy(8,17+i); printf("%s", p->title);
        gotoxy(32,17+i); printf("%s", p->author);
        gotoxy(54,17+i); printf("%s", p->year);
        gotoxy(63,17+i); printf("%s", p->refNum);
        gotoxy(82,17+i); printf("%s", p->material);
        gotoxy(97,17+i); printf("%s", p->category);
        gotoxy(116,17+i); printf("%d", p->shelfNo);
        gotoxy(130,17+i); printf("%d", p->totalStock);
        gotoxy(141,17+i); printf("%d", p->borrower);
        gotoxy(155,17+i); printf("%d", p->totalStock-p->borrower);
        p=p->nxt;
    }

    gotoxy(3,16+i+1); printf("\033[31m____________________________________________________________________________________________________________________________________________________________\n");
    gotoxy(5,16+i+3); printf("\033[0m");
    system("pause");
}

//The save() function prints the information of all the book node in a text file.
void saveBook(){
FILE *fp= fopen("bookDetails.txt", "w+");
BOOK *p;

    if(fp==NULL){
        printf("\nTHE FILE ""bookDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        p=headBook;
        while(p!=NULL){
            fprintf(fp, "%s\n%s\n%s\n%s %s %s %d %d %d\n\n", p->title, p->author, p->category, p->material, p->year, p->refNum, p->shelfNo, p->totalStock, p->borrower);
            p=p->nxt;
        }
        fclose(fp);
    }
}

//retrieve() function retrieves all info from the text file and save each book in the linked list.
void retrieveBook(){
FILE *fp= fopen("bookDetails.txt", "r+");
BOOK *p;

    if(fp==NULL){
        printf("THE FILE ""bookDetails.txt"" DOES NOT EXIST\n");
        system("pause");
    }

    else{
        while(1){
            fflush stdin;
            fscanf(fp, "\n%[^\n]\n", &infoBook.title);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoBook.author);
            fflush stdin;
            fscanf(fp, "%[^\n]\n", &infoBook.category);
            fflush stdin;
                  //\n%[^\n]\n%[^\n]\n", &info.title, &info.author, &info.category);;
            fscanf(fp, "%s %s %s %d %d %d", &infoBook.material, &infoBook.year, &infoBook.refNum, &infoBook.shelfNo, &infoBook.totalStock, &infoBook.borrower);

            //decrypting the retrieved info.
            //strcpy(info.title, decrypt(info.title)); strcpy(info.author, decrypt(info.author)); strcpy(info.category, decrypt(info.category));
            //strcpy(info.year, decrypt(info.year)); strcpy(info.ISBN, decrypt(info.ISBN));

            if(!feof(fp)){
                addBook();
                fflush stdin;
            }
            else{break;}
        }
    }
    fclose(fp);
}

//The menu() function displays the main menu of the library catalog program and prompts the user to enter a choice. It returns the user's choice.
int menuBook(int choice){
    while(choice<1 || choice>6){
        system("cls");
        printf("\tMANAGE BOOK RECORD\n");
        printf("\nMENU");
        printf("\n[1] ADD RECORD");
        printf("\n[2] UPDATE RECORD");
        printf("\n[3] DELETE RECORD");
        printf("\n[4] SEARCH RECORD");
        printf("\n[5] DISPLAY ALL RECORDS");
        printf("\n[6] GO BACK");
        printf("\nENTER OPTION: ");
        scanf("%d", &choice);
        if(choice<1 || choice>6){
            printf("\nSELECT 1-6 ONLY!\n");
            system("pause");
        }
    }
    return choice;
}
