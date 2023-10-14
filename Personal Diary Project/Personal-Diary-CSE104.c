#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int option;

void login();
void main_menu();
void addrecord();
void readrecord();
void editrecord();
void deleterecord();
void editpassword();
void exitdiary();
void select_option();

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
    char username[20], c;
    char password[20];
    char checkuser[20];
    char checkpass[20];
    char *passptr = &checkpass[20];
    char *userptr = &checkuser[20];

    main_menu();
            printf("\t\t\t .-------------.\n");
            printf("\t\t\t<  LOGIN  MENU  >\n");
            printf("\t\t\t '-------------'\n\n");

    if(!strcmp(checkuser,"NULL") && !strcmp(checkpass,"NULL")){
        do{
            printf("\n\n\t\tENTER USERNAME: ");
            gets(username);
            printf("\n\t\tENTER PASSWORD: ");

            while(i<10){
                password[i]=getch();
                c=password[i];
                if(c==13) break;
                else printf("*");
                i++;
            }
            password[i]='\0';
            i=0;
            if(!strcmp(username,checkuser)==0 && !strcmp(password,checkpass)){
                printf("\n\n\t\tSUCCESSFUL LOGIN\n\t\tWelcome Back %s",checkuser);
                printf("\n\n\t\t\PRESS ANY KEY TO CONTINUE...");
                getch();
                break;
            }
            else{
                printf("\n\t\tUSER NOT IDENTIFIED...\n\t\tPRESS ANY KEY TO TRY AGAIN...");
                attempt++;
                getch();
            }
        } while(attempt<3);
            if (attempt>2){
                printf("\n\t\tSorry, you have entered the wrong username and password three times!!!\n\t\tClosing Diary...\n");
                getch();
                exit(0);
            }
            system("cls");
        } else {
            printf("\n\t\tNEW USER IDENTIFIED\n");

            int nflag = 1, pflag = 1;
            while(nflag){
                printf("\n\n\t\tSET USERNAME (10 CHARACTERS MAX): ");
                scanf("%s", *userptr);
                if(strlen(checkuser)>10)
                    printf("\t\tUSERNAME TOO LONG...\nPlease enter 10 characters or below.\n");
                else
                    nflag = 0;
            }
            while(pflag){
                printf("\n\t\tSET PASSWORD (10 DIGITS MAX): ");
                scanf("%s", *passptr);
                if(strlen(checkpass)>10)
                    printf("\t\tPASSWORD TOO LONG...\nPlease enter 10 characters or below.\n");
                else
                    pflag = 0;
            }
            printf("\n\n\tUSER DATA LOGGED SUCCESSFULLY...\n");
            login();
        }
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

    char date[11];
    char time[6];
    char more = 'y';

    printf("\t\tEnter the date of your record\n\t\t(dd/mm/yyyy) : ");
    fflush(stdin);
    scanf("%s", date);

    FILE *fptr = fopen(date, "ab+");

    if (fptr==NULL ){
        fptr=fopen(date,"wb+");
        if(fptr==NULL){

            printf("\n\t\tSYSTEM ERROR...\n");
            printf("\t\tPRESS ANY KEY TO EXIT\n");
            getch();
            return ;
        }
    }

    while(more=='Y' || more=='y'){
        fflush(stdin);
        scanf("%s", time);

    }

    fclose(fptr);
    printf("\n\n\tPRESS ANY KEY TO EXIT\n");
    getch();
}

void readrecord(){
    return 0;
}

void editrecord(){
    return 0;
}

void deleterecord(){
    return 0;
}

void editpassword(){

}

void exit_diary(){
    printf("\n\n\t\tThank you for using the program ~ <3\n\n");
    printf("\t\t      wWWWw\t\t wWWWw\n");
    printf("\t\tvVVVv (___) wWWWw\t (___)  vVVVv\n");
    printf("\t\t(___)  ~Y~  (___)  vVVVv  ~Y~   (___)\n");
    printf("\t\t ~Y~   \\|    ~Y~   (___)   |/    ~Y~\n");
    printf("\t\t \\|   \\ |/   \\| /   ~Y~   \\|    \\ |/\n");
    printf("\t\t \\|/   \\|/   \\|/    \\|/   \\|/    \\\|/ \n");
    printf("\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\t\tart by: Joan G. Stark\n");
}


