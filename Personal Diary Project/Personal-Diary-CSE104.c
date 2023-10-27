#include<stdlib.h>
#include<stdio.h>
#include<string.h>

char date[14];
char time[8];

void banner();
void login();
void select_option();
void addrecord();
void readrecord();
void deleterecord();
void editpassword();
void exit_diary();

struct record{
    char date[14];
    char time[8];
    char body[1000];
} r ;

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
    printf("\t\t\t\t .------------.\n");
    printf("\t\t\t\t<  LOGIN MENU  >\n");
    printf("\t\t\t\t '------------'\n\n");

    FILE *fptr = fopen("userdata", "r");

    fseek (fptr, 0, SEEK_END);
    if(fptr==NULL || !ftell(fptr)){
        printf("\t\tNEW USER DETECTED\n\n\t\tPRESS ANY KEY TO CONTINUE...\n\t\t");
        getch();
        editpassword(1);
    }

    rewind(fptr);
    char checkpass[20];
    fgets(checkpass, 21, fptr);

    do{
        printf("\n\t\tENTER PASSWORD : ");

        while(i<21){
            givenpass[i]=getch();
            c=givenpass[i];
            if(c==13) break;
            else printf("*");
            i++;
        }
        givenpass[i]='\0';
        i=0;

        if(!strcmp(checkpass,givenpass)){
            printf("\n\n\t\tSUCCESSFUL LOGIN\n\n\t\tWelcome Back!\n");
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
        } else {
            printf("\n\n\t\tClosing Diary...\n\n\n");
            printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY");
            getch();
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

    char opt;

    while(1){

        banner();
        printf("\t\t\t\t .-------------.\n");
        printf("\t\t\t\t<   MAIN MENU   >\n");
        printf("\t\t\t\t '-------------'\n\n");
        printf("\t\t(1). Add Record\n\t\t(2). View Record\n");
        printf("\t\t(3). Delete Record\n\t\t(4). Change Password\n");
        printf("\t\t(0). Exit\n\n\t\tEnter your choice: ");

        scanf(" %c", &opt);

        if(opt>'5' || opt<'0'){
            printf("\n\t\tYou've entered the wrong choice\n\n\t\tPRESS ANY KEY TO TRY AGAIN\n\t\t");
            getch();
            system("cls");
        } else
            break;
    }

    switch (opt){
        case '1':
            addrecord();
            break;
        case '2':
            readrecord();
            break;
        case '3':
            deleterecord();
            break;
        case '4':
            editpassword();
            break;
        case '0':
            exit_diary();
            break;
    }
}

void addrecord(){

    char more = 'y'; int f = 0;

    while(more=='Y' || more=='y'){

        system("cls");
        banner();
        printf("\t\t\t\t .--------------.\n");
        printf("\t\t\t\t<  Add Record... >\n");
        printf("\t\t\t\t '--------------'\n\n");

        printf("\t\tENTER DATE:\n\t\t(DD.MM.YYYY) : ");
        scanf("%s", date);
        strncat(date, ".txt", 4);

        FILE *fptr = fopen(date, "a");

        printf("\n\t\tENTER TIME:\n\t\t(HH.MM XM) : ");
        scanf(" %[^\n]c", time);
        strcpy(r.time, time);

        printf("\n\t\tENTER RECORD:\n\t\t");
        scanf(" %[^\n]s", r.body);

        fwrite(&r, sizeof(r), 1, fptr);

        printf("\n\t\tYOUR RECORD IS ADDED...\n");
        fclose(fptr);

        printf("\n\t\tWILL YOU ADD ANOTHER RECORD? (Y/N): ") ;
        more = getch();
    }


    printf("\n\n\t\t(1) Go Back\t(0) Exit\n\n\t\tEnter your choice: ");
    if(getch()=='1'){
        system("cls");
        select_option();
    }
    else
        exit_diary();

}

void readrecord(){

    while(1){

        system("cls");
        banner();
        printf("\t\t\t\t .---------------.\n");
        printf("\t\t\t\t<  Read Record... >\n");
        printf("\t\t\t\t '---------------'\n\n");

        printf("\t\tENTER DATE:\n\t\t(DD.MM.YYYY) : ");
        scanf("%s", date);
        strncat(date, ".txt", 4);
        FILE *fptr = fopen(date, "r");

        fseek (fptr, 0, SEEK_END);

        if(fptr==NULL || !ftell(fptr))
            printf("\n\t\tNO RECORDS MADE ON THIS DATE\n");
        else {
            char readdate[10];
            strncat(readdate, date, 10);
            printf("\n\t\tTHE RECORDS OF %s ARE:\n",readdate);
            rewind(fptr);
            while(fread(&r, sizeof(r), 1, fptr)== 1){
                char *str = r.time;
                printf("\n\t\tTIME   : %.8s",str);
                printf("\n\t\tRECORD : %s\n",r.body);
            }
        }

        fclose(fptr);

        printf("\n\n\t\t(1) Go Back    (2) Read Another Record    (0) Exit\n\n\t\tEnter your choice: ");
        char c = getch();
        if(c!='2' && c!='0'){
            system("cls");
            select_option();
        } else if(c=='0')
            exit_diary();
    }

}

void deleterecord(){

    while(1){
        system("cls");
        banner();
        printf("\t\t\t\t .-----------------.\n");
        printf("\t\t\t\t<  Delete Record... >\n");
        printf("\t\t\t\t '-----------------'\n\n");

        printf("\n\t\tENTER DATE:\n\t\t(DD.MM.YYYY) : ");
        scanf("%s", date);
        strncat(date, ".txt", 4);
        FILE *fptr = fopen(date, "w"), *temptr;

        fseek (fptr, 0, SEEK_END);

        if(fptr==NULL || !ftell(fptr))
            printf("\n\t\tNO RECORDS MADE ON THIS DATE\n");
        else {
            printf("\n\n\t\tWHAT WOULD YOU LIKE TO DO:");
            printf("\n\n\t\t(1) DELETE A WHOLE DAY'S ENTRY\n\t\t(2) DELETE A SINGLE ENTRY OF A DAY");
            int choice;

            while(1){
                printf("\n\n\t\tENTER YOU CHOICE: ");
                scanf("%d", &choice);
                if(choice!=1 && choice!=2){
                    printf("\n\t\tYou've entered the wrong choice\n\n\t\tPRESS ANY KEY TO TRY AGAIN\n\t\t");
                    getch();
                } else
                    break;
            }

            switch(choice){
                case 1:
                    fclose(fptr);
                    remove(date);
                    printf("\n\t\tTHE RECORD HAS BEEN DELETED SUCCESFULLY...");
                    break;
                case 2:
                    temptr = fopen("temp", "w");
                    printf("\n\t\tENTER TIME:\n\t\t(HH.MM XM) : ");
                    scanf(" %[^\n]c", time);

                    while(fread(&r, sizeof(r), 1, fptr)==1){
                        char comptime[8];
                        strncat(comptime, r.time, 8);
                        if(strcmp(comptime,time)!=0)
                            fwrite(&r, sizeof(r), 1, temptr);
                    }
                    fclose(fptr);
                    fclose(temptr);
                    remove(date);
                    rename("temp",date);
                    printf("\n\t\tTHE RECORD HAS BEEN DELETED SUCCESFULLY...");
                    break;
            }
        }

        printf("\n\n\t\t(1) Go Back    (2) Delete Another Record    (0) Exit\n\n\t\tEnter your choice: ");
        char c = getch();
        if(c!='2' && c!='0'){
            system("cls");
            select_option();
        } else if(c=='0')
            exit_diary();
    }

}

void editpassword(int newuserdetect){

    system("cls");
    banner();
    printf("\t\t\t\t .---------------.\n");
    printf("\t\t\t\t<  Edit Password  >\n");
    printf("\t\t\t\t '---------------'\n\n");

    int a = 0, i = 0;

    if(newuserdetect!=1){
        FILE *fptr = fopen("userdata", "r");
        char old[20], inp[20], c;
        fgets(old, 21, fptr);

        do{
            printf("\n\t\tENTER THE CURRENT PASSWORD: ");

            while(i<21){
                inp[i] = getch();
                c = inp[i];
                if(c==13) break;
                else printf("*");
                i++;
            }
            inp[i]='\0';
            i=0;

            if(!strcmp(inp,old)){
                printf("\n\n\t\tUSER VERIFIED...");
                break;
            }
            else{
                printf("\n\t\tINCORRECT PASSWORD...\n");
                a++;
            }
        } while(a<3);

        fclose(fptr);
        if(a>2){
            printf("\n\t\tWRONG PASSWORD ENTERED THREE TIMES!\n\t\tACCESS DENIED!\n\n\t\tClosing Diary...\n\n\n");
            printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY");
            getch();
            exit(0);
        }
    }

    int flg = 0;
    do{
        FILE *fptr = fopen("userdata", "w");

        i=0;
        char pass[20] = {0}, confirm[20] = {0}, ch;

        printf("\n\n\t\tENTER THE NEW PASSWORD: ");
        pass[0] = getch();
        printf("%c", pass[i]);

        while(pass[i]!='\r'){
            if(pass[i]=='\b'){
                i--;
                printf(" ");
                printf("\b");
                printf(" ");
                printf("\b");
                pass[i]=getch();
                printf("%c",pass[i]);

            }
            else{
                i++;
                pass[i]=getch();
                printf("%c",pass[i]);
            }
        }
        pass[i]='\0';
        i=0;

        printf("\n\t\tPLEASE CONFIRM THE PASSWORD: ");
        confirm[0] = getch();
        printf("%c", confirm[i]);

        while(confirm[i]!='\r'){
            if(confirm[i]=='\b'){
                i--;
                printf(" ");
                printf("\b");
                printf(" ");
                printf("\b");
                confirm[i]=getch();
                printf("%c",confirm[i]);
            }
            else{
                i++;
                confirm[i]=getch();
                printf("%c",confirm[i]);
            }
        }
        confirm[i]='\0';

        if(!strcmp(pass,confirm)){
            i=0;
            while(pass[i]!='\0'){
                ch = pass[i];
                putc(ch,fptr);
                i++;
            }
            fclose(fptr);
            flg = 0;
        }
        else{
            printf("\n\t\tTHE NEW PASSWORD DOES NOT MATCH.");
            flg = 1;
            fclose(fptr);
        }

    } while(flg);

    printf("\n\n\t\tPASSWORD CHANGED SUCCESSFULLY...\n\n\t\tPLEASE LOGIN AGAIN!\n\n\t\tClosing Diary...\n\n");
    printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY");
    getch();
    exit(0);
}

void exit_diary(){

    system("cls");
    banner();
    printf("\n\n\t\tThank you for using the program ~ <3\n\n\n");
    printf("\t\t       wWWWw\t\t wWWWw\n");
    printf("\t\tvVVVv  (___) wWWWw\t (___)  vVVVv\n");
    printf("\t\t(___)   ~Y~  (___)  vVVVv  ~Y~   (___)\n");
    printf("\t\t ~Y~    \\|    ~Y~   (___)   |/    ~Y~\n");
    printf("\t\t \\|    \\ |/   \\| /   ~Y~   \\|    \\ |/\n");
    printf("\t\t \\|/    \\|/   \\|/    \\|/   \\|/    \\\|/ \n");
    printf("\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\t\tart by: Joan G. Stark\n\n\n");
    printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY");
    getch();
    exit(0);

}





