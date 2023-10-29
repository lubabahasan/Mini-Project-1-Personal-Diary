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
void deletesingle();
void editpassword();
void exit_diary();

struct record{
    char rtime[8];
    char rbody[1000];
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
        printf("\t\tNEW USER DETECTED\n\n\t\tPRESS ANY KEY TO CONTINUE...");
        getch();
        editpassword(1);
    }

    fseek(fptr, 0, SEEK_SET);
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
        printf("\n\t\tWRONG PASSWORD ENTERED THREE TIMES!\n\t\tACCESS DENIED!\n\n\t\tClosing Diary...\n\n");
        printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY\n\n");
        getch();
        exit(0);
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
        printf("%c", opt);

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

    while(1){

        system("cls");
        banner();
        printf("\t\t\t\t .--------------.\n");
        printf("\t\t\t\t<  Add Record... >\n");
        printf("\t\t\t\t '--------------'\n\n");

        while(1){
            printf("\t\tENTER DATE:\n\t\t(DD.MM.YYYY) : ");
            scanf("%s", date);
            if(strlen(date)!=10)
                printf("\n\t\tPLEASE ENTER A VALID DATE\n");
            else
                break;
        }
        strncat(date, ".txt", 4);
        FILE *fptr = fopen(date, "a");

        while(1){
            printf("\n\t\tENTER TIME:\n\t\t(HH.MM XM)   : ");
            int i=0; char c;
            while(1){
                c = getch();
                if(c==13)
                    break;
                else{
                    time[i] = c;
                    printf("%c", c);
                }
                i++;
            }
            time[i]='\0';
            if(i!=8)
                printf("\n\t\tPLEASE ENTER A VALID TIME");
            else{
                strcpy(r.rtime, time);
                break;
            }
        }

        fflush(stdin);

        printf("\n\n\t\tENTER RECORD (PRESS 'ENTER' TO SAVE RECORD):\n\n\t\t");
        scanf(" %[^\n]s", r.rbody);

        fwrite(&r, sizeof(r), 1, fptr);

        printf("\n\t\tYOUR RECORD IS ADDED...");
        fclose(fptr);

        printf("\n\n\t\t(1) Go Back    (2) Add Another Record    (0) Exit\n\n\t\tEnter your choice: ");
        char c = getch();
        printf("%c", c);
        printf("\n\n\t\tPRESS ANY KEY TO CONTINUE...");
        getch();
        if(c!='2' && c!='0'){
            system("cls");
            select_option();
        } else if(c=='0')
            exit_diary();
    }

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
            char readdate[10] = {0};
            strncat(readdate, date, 10);
            printf("\n\t\tTHE RECORDS OF %s ARE:\n",readdate);
            fseek(fptr, 0, SEEK_SET);
            while(fread(&r, sizeof(r), 1, fptr)== 1){
                char *str = r.rtime;
                printf("\n\t\tTIME   : %.8s",str);
                printf("\n\t\tRECORD : %s\n",r.rbody);
            }
        }

        fclose(fptr);

        printf("\n\n\t\t(1) Go Back    (2) Read Another Record    (0) Exit\n\n\t\tEnter your choice: ");
        char c = getch();
        printf("%c", c);
        printf("\n\n\t\tPRESS ANY KEY TO CONTINUE...");
        getch();
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
        printf("\n\t\tWHAT WOULD YOU LIKE TO DO:");
        printf("\n\n\t\t(1) DELETE A WHOLE DAY'S ENTRY\n\t\t(2) DELETE A SINGLE ENTRY OF A DAY");

        char choice;
        while(1){
            printf("\n\n\t\tENTER YOUR CHOICE: ");
            fflush(stdin);
            scanf( "%c", &choice);
            if(choice!='1' && choice!='2'){
                printf("\n\t\tYou've entered the wrong choice.");
            } else
                break;
        }

        while(1){
            printf("\n\t\tENTER DATE\n\t\t(DD.MM.YYYY) : ");
            scanf("%s", date);
            if(strlen(date)!=10)
                printf("\n\t\tPLEASE ENTER A VALID DATE\n");
            else
                break;
        }

        strncat(date, ".txt", 4);
        FILE *fptr = fopen(date, "r");
        fseek (fptr, 0, SEEK_END);

        if(fptr==NULL || !ftell(fptr))
            printf("\n\t\tNO RECORDS MADE ON THIS DATE\n");
        else {
            switch(choice){
                case '1':
                    fclose(fptr);
                    remove(date);
                    printf("\n\t\tTHE RECORD HAS BEEN DELETED SUCCESSFULLY...");
                    break;
                case '2':
                    fclose(fptr);
                    deletesingle();
                    break;
            }
        }

        printf("\n\n\t\t(1) Go Back    (2) Delete Another Record    (0) Exit\n\n\t\tEnter your choice: ");
        char c;
        fflush(stdin);
        scanf( "%c", &c);
        printf("\n\n\t\tPRESS ANY KEY TO CONTINUE...");
        getch();
        if(c!='2' && c!='0'){
            system("cls");
            select_option();
        } else if(c=='0')
            exit_diary();
    }
}

void deletesingle(){

    char comptime[8];
    FILE *fptr = fopen(date, "r"), *temptr = fopen("temp.txt", "w");

    char deldate[10];
    strncat(deldate, date, 10);
    printf("\n\t\tTHE RECORDS OF %s ARE:\n", deldate);

    while(fread(&r, sizeof(r), 1, fptr)==1){
        char *str = r.rtime;
        printf("\n\t\tTIME   : %.8s",str);
        printf("\n\t\tRECORD : %s\n",r.rbody);
    }

    printf("\n\t\tENTER TIME\n\t\t(HH.MM XM)   : ");

    fflush(stdin);
    fgets(time, 9, stdin);
    fseek(fptr, 0, SEEK_SET);

    while(fread(&r, sizeof(r), 1, fptr)==1){
        strncpy(comptime, r.rtime, 8);
        comptime[8]='\0';
        if(strcmp(comptime,time)!=0){
            fwrite(&r, sizeof(r), 1, temptr);
        }
    }
    fclose(fptr);
    fclose(temptr);

    printf("\n\t\tARE YOU SURE YOU WANT TO DELETE THIS RECORD?\n\t\tENTER DATE TO CONFIRM (DD.MM.YYYY) : ");
    fflush(stdin);
    scanf(" %s", date);
    strncat(date, ".txt", 4);

    if(!remove(date) && !rename("temp.txt", date))
        printf("\n\t\tTHE RECORD HAS BEEN DELETED SUCCESSFULLY...");
    else
        printf("\n\t\tTHE RECORD COULD NOT BE DELETED, PLEASE ENSURE THE DATA ENTERED IS CORRECT...");

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
            printf("\n\t\tWRONG PASSWORD ENTERED THREE TIMES!\n\t\tACCESS DENIED!\n\n\t\tClosing Diary...\n\n");
            printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY\n\n");
            getch();
            exit(0);
        }
    }

    int flg = 0;
    do{
        FILE *fptr = fopen("userdata", "w");

        char pass[20] = {0}, confirm[20] = {0}, ch;

        printf("\n\n\t\tENTER THE NEW PASSWORD (20 CHARACTER MAX) : ");
        scanf(" %[^\n]c",pass);
        pass[strlen(pass)]='\0';

        printf("\n\t\tPLEASE CONFIRM THE PASSWORD\t\t  : ");
        scanf(" %[^\n]c",confirm);
        confirm[strlen(confirm)]='\0';

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
    printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY\n\n");
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
    printf("\n\n\t\tPRESS ANY KEY TO CLOSE THE DIARY\n\n");
    getch();
    exit(0);

}





