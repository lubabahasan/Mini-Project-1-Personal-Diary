#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char date[11];
char time[6];

void login();
void banner();
void addrecord();
void readrecord();
void editrecord();
void deleterecord();
void editpassword();
void exit_diary();
void select_option();

struct entry_record{
    char time[6];
    char body[7000];
};

int main()
{
    login();
    select_option();

    return 0;
}

void login(){

	int attempt=0,i=0;
    char c;
    char givenpass[20];

    banner();
    printf("\t\t\t .-------------.\n");
    printf("\t\t\t<  LOGIN  MENU  >\n");
    printf("\t\t\t '-------------'\n\n");

    FILE *fptr = fopen("userdata", "r");

    do{
        printf("\n\t\tENTER PASSWORD: ");

        while(i<21){
            givenpass[i]=getch();
            c=givenpass[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        givenpass[i]='\0';

        char checkpass[20];
        fgets(checkpass, 21, fptr);

        i=0;

        if(!strcmp(checkpass,givenpass)){
            printf("\n\n\t\tSUCCESSFUL LOGIN\n\t\tWelcome Back\n");
            printf("\n\n\t\t\PRESS ANY KEY TO CONTINUE...");
            getch();
            system("cls");
            break;
        }
        else{
            printf("\n\t\tINCORRECT PASSWORD...\n");
            attempt++;
        }
    } while(attempt<3);

    if(attempt>2){
        printf("\n\t\tSorry, you have entered the wrong password three times!!!\n\t\tDO YOU WANT TO TRY AGAIN (Y/N)? : ");
        char opt;
        scanf(" %c", &opt);

        fclose(fptr);

        if(opt=='Y' || opt=='y'){
            system("cls");
            login();
        }
        else {
            printf("\n\n\t\tClosing Diary...\n\n\n");
            exit(0);
        }
    }
}

void banner(){

    printf("\t\t  __   __  __   __    ______   ___   _______  ______     __   __\n");
    printf("\t _( )_   |  |_|  ||  | |  |  |  _   | |   | |   _   ||    _  \\  |  | |  |    _( )_\n");
    printf("\t(_ o _)  |       ||  |_|  |  | | |   ||   | |  |_|  ||   |_| |  |  |_|  |   (_ o _)\n");
    printf("\t (_-_)   | ||_|| ||_     _|  | |_|   ||   | |       ||    __  \\ |_     _|    (_-_)\n");
    printf("\t\t |_|   |_|  |___|    |______| |___| |__| |__||___|  |_|   |___|\n\n");
    printf("\t      ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n\n");

}

void select_option(){

    char option;

    while(1){

        banner();
        printf("\t\t\t .-------------.\n");
        printf("\t\t\t<   MAIN MENU   >\n");
        printf("\t\t\t '-------------'\n\n");
        printf("\t\t(1). Add Entry\n\t\t(2). View Entry\n");
        printf("\t\t(3). Edit Entry\n\t\t(4). Delete Entry\n");
        printf("\t\t(5). Change Password\n\t\t(6). Exit\n\n");
        printf("\t\tEnter your choice: ");

        scanf(" %c", &option);

        if(option>'6' || option<'1'){
            printf("\n\t\tYou've entered the wrong choice\n\n\t\tPRESS ANY KEY TO TRY AGAIN\n\t\t");
            getch();
            option = 0;
            system("cls");
        } else
            break;
    }

    switch (option){
        case '1':
            addrecord();
            break;
        case '2':
            readrecord();
            break;
        case '3':
            editrecord();
            break;
        case '4':
            deleterecord();
            break;
        case '5':
            editpassword();
            break;
        case '6':
            exit_diary();
            exit(0);
            break;
    }
}

void addrecord(){

    system("cls");
    banner();
    printf("\t\t\t .--------------.\n");
    printf("\t\t\t<  Add Record... >\n");
    printf("\t\t\t '--------------'\n\n");


    char more = 'y';

    printf("\t\tEnter the date of your record\n\t\t(dd.mm.yyyy) : ");
    fflush(stdin);
    scanf("%s", date);

    FILE *fptr = fopen(date, "a+");

    /*if (fptr==NULL ){
        fptr=fopen(date,"a+");
        if(fptr==NULL){

            printf("\n\t\tSYSTEM ERROR...\n");
            printf("\t\tPRESS ANY KEY TO EXIT\n");
            getch();
            return ;
        }
    }*/

    while(more=='Y' || more=='y'){
        fflush(stdin);
        printf("\t\tEnter the time of your record\n\t\t(hh.mm) : ");
        scanf("%s", time);

    }

    fclose(fptr);
    printf("\n\n\tPRESS ANY KEY TO EXIT\n");
    getch();
}

void readrecord(){

    system("cls");
    banner();
    printf("\t\t\t .---------------.\n");
    printf("\t\t\t<  Read Record... >\n");
    printf("\t\t\t '---------------'\n\n");

    int ch;

    printf("\t\tEnter the date of the record\n\t\t(dd.mm.yyyy) : ");
    fflush(stdin);
    scanf("%s", date);
    fflush(stdin);
    printf("\t\tEnter the time of the record\n\t\t(hh.mm) : ");
    scanf("%s", time);

    system("cls");

    FILE *fptr = fopen(date, "a+");

    banner();
    printf("\t\tRecord of %s\n", date);
    printf("\n\t\t-------------------\n\t\t");
    do{
        if(ch==10)
            printf("\t\t-------------------\n\t\t");
        ch = fgetc(fptr);
        printf("%c", ch);
    } while (ch != EOF);
    printf("\n\t\t-------------------\n");

    printf("\n\n\n\t\tWHAT WOULD YOU LIKE TO DO NEXT :\n\n\t\t(1). Read Another Record\n\t\t(2). Go to Main Menu\n\t\t(3). Exit Program\n\n\t\tEnter your choice: ");

        int choice;
        scanf("%d", &choice);

        system("cls");

        if(choice == 1){
            login();
        } else {
            exit_diary();
        }

    fclose(fptr);
}

void editrecord(){

    system("cls");
    banner();
    printf("\t\t\t .---------------.\n");
    printf("\t\t\t<  Edit Record... >\n");
    printf("\t\t\t '---------------'\n\n");

}

void deleterecord(){

    system("cls");
    banner();
    printf("\t\t\t .-----------------.\n");
    printf("\t\t\t<  Delete Record... >\n");
    printf("\t\t\t '-----------------'\n\n");

}

void editpassword(){

    FILE *fptr = fopen("userdata", "r");
    char newuser[20];
    fgets(newuser, 21, fptr);
    fclose(fptr);

    system("cls");
    banner();
    printf("\t\t\t .---------------.\n");
    printf("\t\t\t<  Edit Password  >\n");
    printf("\t\t\t '---------------'\n\n");

    if(!strcmp(newuser,"PSNY")); //PasswordNotSetYet
        printf("\t\tPLEASE SET A NEW PASSWORD: ");

    /*int passflag = 1;
    char temppass[30];

    while(passflag){
        printf("\t\tSET PASSWORD (20 CHARACTERS MAX): ");\
        fgets(temppass, 30, stdin);
        if(strlen(temppass)>20)
            printf("\n\t\tPASSWORD LONGER THAN 2O CHARACTERS...\n\n");
        else
            printf("\t\tPASSWORD CHANGED SUCCESSFULLY\n");
            passflag = 0;
    }

    FILE *fptr = fopen ("userdata", "r+");

    fprintf(fptr, temppass);
    fclose(fptr);

    printf("\n\t\tWHAT WOULD YOU LIKE TO DO :\n\n\t\t(1). Go to Login Menu\n\t\t(2). Exit Program\n\n\t\tEnter your choice: ");

    int choice;
    scanf("%d", &choice);

    system("cls");
    if(choice == 1){
        login();
    } else {
        exit_diary();
    }
    */
}

void exit_diary(){

    system("cls");
    printf("\n\n\t\tThank you for using the program ~ <3\n\n");
    printf("\t\t      wWWWw\t\t wWWWw\n");
    printf("\t\tvVVVv (___) wWWWw\t (___)  vVVVv\n");
    printf("\t\t(___)  ~Y~  (___)  vVVVv  ~Y~   (___)\n");
    printf("\t\t ~Y~   \\|    ~Y~   (___)   |/    ~Y~\n");
    printf("\t\t \\|   \\ |/   \\| /   ~Y~   \\|    \\ |/\n");
    printf("\t\t \\|/   \\|/   \\|/    \\|/   \\|/    \\\|/ \n");
    printf("\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\t\tart by: Joan G. Stark\n");
    exit(0);

}


