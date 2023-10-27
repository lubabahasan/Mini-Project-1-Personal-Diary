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
void editrecord();
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
    printf("\t\t\t .------------.\n");
    printf("\t\t\t<  LOGIN MENU  >\n");
    printf("\t\t\t '------------'\n\n");

    FILE *fptr = fopen("userdata", "r");
    char checkpass[20];
    fgets(checkpass, 21, fptr);
    if(!strcmp(checkpass,"PNSY")){ //PasswordNotSetYet
        fclose(fptr);
        printf("\t\tNEW USER DETECTED\n\n\t\tPRESS ANY KEY TO CONTINUE...\n\t\t");
        getch();
        editpassword(1);
    }

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

    char opt;

    while(1){

        banner();
        printf("\t\t\t .-------------.\n");
        printf("\t\t\t<   MAIN MENU   >\n");
        printf("\t\t\t '-------------'\n\n");
        printf("\t\t(1). Add Record\n\t\t(2). View Record\n");
        printf("\t\t(3). Edit Record\n\t\t(4). Delete Record\n");
        printf("\t\t(5). Change Password\n\t\t(6). Exit\n\n");
        printf("\t\tEnter your choice: ");

        scanf(" %c", &opt);

        if(opt>'6' || opt<'1'){
            printf("\n\t\tYou've entered the wrong choice\n\n\t\tPRESS ANY KEY TO TRY AGAIN\n\t\t");
            getch();
            opt = 0;
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

    char more = 'y'; int f = 0;

    while(more=='Y' || more=='y'){

        system("cls");
        banner();
        printf("\t\t\t .--------------.\n");
        printf("\t\t\t<  Add Record... >\n");
        printf("\t\t\t '--------------'\n\n");

        printf("\t\tENTER DATE:\n\t\t(DD.MM.YYYY) : ");
        scanf("%s", date);
        strncat(date, ".txt", 4);
        FILE *fptr = fopen(date, "a");

        printf("\n\t\tENTER TIME:\n\t\t(HH.MM XM) : ");
        scanf(" %[^\n]c", time);

        strcpy(r.time, time);
        printf("\n\t\tENTER RECORD:\n\t\t");

        scanf(" %[^\n]s", r.body);

        fwrite(&r,sizeof(r),1,fptr);

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

    int more = 1;

    while(more){

        system("cls");
        banner();
        printf("\t\t\t .---------------.\n");
        printf("\t\t\t<  Read Record... >\n");
        printf("\t\t\t '---------------'\n\n");

        printf("\t\tENTER DATE:\n\t\t(dd.mm.yyyy) : ");
        scanf("%s", date);

        strncat(date, ".txt", 4);
        FILE *fptr = fopen(date, "r");

        if(fptr==NULL)
            printf("\n\t\tNO RECORDS MADE ON THIS DATE\n");
        else{
            fseek(fptr, 0, SEEK_END);
            if(!ftell(fptr)) {
                printf("\n\t\tNO RECORDS MADE ON THIS DATE\n");
            } else {
                char *dtr = r.date;
                printf("\n\t\tTHE RECORDS OF %.10s ARE:\n",dtr);
                rewind(fptr);
                while(fread(&r, sizeof(r), 1, fptr)== 1 ){
                    char *str = r.time;
                    printf("\n\t\tTIME   : %.8s",str);
                    printf("\n\t\tRECORD : %s\n",r.body);
                }
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

void editpassword(int newuserdetect){

    system("cls");
    banner();
    printf("\t\t\t .---------------.\n");
    printf("\t\t\t<  Edit Password  >\n");
    printf("\t\t\t '---------------'\n\n");

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
            exit(0);
        }
    }

    int flg = 0;
    do{
        FILE *fptr = fopen("userdata", "w");

        i=0;
        char pass[20] = {0}, confirm[20] = {0}, ch;

        printf("\n\n\t\tENTER THE NEW PASSWORD: ");
        //fflush(stdin);
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

    exit(0);
}

void exit_diary(){

    system("cls");
    banner();
    printf("\n\n\t\tThank you for using the program ~ <3\n\n");
    printf("\t\t      wWWWw\t\t wWWWw\n");
    printf("\t\tvVVVv (___) wWWWw\t (___)  vVVVv\n");
    printf("\t\t(___)  ~Y~  (___)  vVVVv  ~Y~   (___)\n");
    printf("\t\t ~Y~   \\|    ~Y~   (___)   |/    ~Y~\n");
    printf("\t\t \\|   \\ |/   \\| /   ~Y~   \\|    \\ |/\n");
    printf("\t\t \\|/   \\|/   \\|/    \\|/   \\|/    \\\|/ \n");
    printf("\t\t^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\t\tart by: Joan G. Stark\n\n\n");
    exit(0);

}





