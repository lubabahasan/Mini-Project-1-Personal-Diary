#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int option;
char date[11];
char time[6];

void login();
void main_menu();
void addrecord();
void readrecord();
void editrecord();
void deleterecord();
void editpassword();
void exit_diary();
void select_option();
int check_empty();

struct entry_record{
    char time[6];
    char body[7000];
};

int main()
{
    login();
    main_menu();
    select_option();

    return 0;
}

void login(){

	int attempt=0,i=0;
    char c;
    char checkpass[20];

    main_menu();
            printf("\t\t\t .-------------.\n");
            printf("\t\t\t<  LOGIN  MENU  >\n");
            printf("\t\t\t '-------------'\n\n");

    FILE *fptr = fopen("userdata", "a+");

    if(check_empty()){
        do{
            printf("\n\t\tENTER PASSWORD: ");

            while(i<21){
                checkpass[i]=getch();
                c=checkpass[i];
                if(c==13) break;
                else printf("*");
                i++;
            }
            i=0;


            if(1){
                printf("\n\n\t\tSUCCESSFUL LOGIN\n\t\tWelcome Back\n");
                printf("\n\n\t\t\PRESS ANY KEY TO CONTINUE...");
                getch();
                break;
            }
            else{
                printf("\n\t\tINCORRECT PASSWORD...\n");
                attempt++;
            }
        } while(attempt<3);

        if (attempt>2){
            printf("\n\t\tSorry, you have entered the wrong password three times!!!\n\t\tClosing Diary...\n");
            exit(0);
        }

        system("cls");

    } else {

        printf("\n\t\tNEW USER IDENTIFIED\n");
        editpassword();
    }
    fclose(fptr);
}

void main_menu(){
    printf("\t\t  __   __  __   __    ______   ___   _______  ______     __   __\n");
    printf("\t _( )_   |  |_|  ||  | |  |  |  _   | |   | |   _   ||    _  \\  |  | |  |    _( )_\n");
    printf("\t(_ o _)  |       ||  |_|  |  | | |   ||   | |  |_|  ||   |_| |  |  |_|  |   (_ o _)\n");
    printf("\t (_-_)   | ||_|| ||_     _|  | |_|   ||   | |       ||    __  \\ |_     _|    (_-_)\n");
    printf("\t\t |_|   |_|  |___|    |______| |___| |__| |__||___|  |_|   |___|\n\n");
    printf("\t      ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n\n");

}

void select_option(){

    printf("\t\t\t .-------------.\n");
    printf("\t\t\t<   MAIN MENU   >\n");
    printf("\t\t\t '-------------'\n\n");
    printf("\t\t(1). Add Entry\n\t\t(2). View Entry\n");
    printf("\t\t(3). Edit Entry\n\t\t(4). Delete Entry\n");
    printf("\t\t(5). Change Password\n\t\t(6). Exit\n\n");
    printf("\t\tEnter your choice: ");

    scanf("%d", &option);

    int select = 1;

    while(select){
        switch (option){
            case 1:
                addrecord();
                break;
            case 2:
                readrecord();
                break;
            case 3:
                editrecord();
                break;
            case 4:
                deleterecord();
                break;
            case 5:
                editpassword();
                break;
            case 6:
                exit_diary();
                exit(0);
                break;
            default:
                printf("\n\n\t\tYou've entered the wrong choice\n\n\t\tPRESS ANY KEY TO TRY AGAIN\n");
                getch();
                break;
        }
        system("cls");
    }
}

void addrecord(){
    system("cls");
    main_menu();
    printf("\t\t\t .-------------.\n");
    printf("\t\t\t<  Add Entry... >\n");
    printf("\t\t\t '-------------'\n\n");


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

    int ch;

    printf("\t\tEnter the date of the record\n\t\t(dd.mm.yyyy) : ");
    fflush(stdin);
    scanf("%s", date);
    fflush(stdin);
    printf("\t\tEnter the time of the record\n\t\t(hh.mm) : ");
    scanf("%s", time);

    system("cls");

    FILE *fptr = fopen(date, "a+");

    main_menu();
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
    return 0;
}

void deleterecord(){
    return 0;
}

void editpassword(){
    int passflag = 1;
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

        FILE *fptr = fopen ("userdata", "a+");

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

int check_empty(){
    FILE *fptr = fopen("userdata", "a+");
    if(fgetc(fptr)==EOF)
        return 0;
    else
        return 1;
    fclose(fptr);
}


