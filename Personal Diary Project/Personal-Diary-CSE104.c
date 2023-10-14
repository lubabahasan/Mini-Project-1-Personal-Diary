#include<stdlib.h>
#include<stdio.h>
#include<string.h>

int option;

void main_menu();
void addrecord();
void readrecord();
void editrecord();
void deleterecord();
void editpassword();

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
                printf("\n\n\t\tTHANK YOU FOR USING THE SOFTWARE ~ <3\n");
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

int main()
{
    main_menu();
    select_option();

    char username[20]="Lubaba";
    char date[10];
    char reader;

    scanf("%s", date);     // entries the filename
    FILE *fptr;
    fptr = fopen(date, "ab+"); // opens/creates that file


    /*//copies contents of template - start
    reader = fgetc(header);
    while (reader != EOF){
        fputc(reader, fptr);
        reader = fgetc(header);
    }
    fclose(fptr);
    //copies contents of template - end*/

    switch(option){
        case 1:
            //opens, reads, prints and closes file - start
            fptr = fopen(date, "ab+");
            if(fptr == NULL)
                printf("No such entry\n");
            else
                printf("The entry for %.8s is:\n\n",date);

            reader = fgetc(fptr);
            while (reader != EOF){
                printf ("%c", reader);
                reader = fgetc(fptr);
            }
            printf("\n\n");

            fclose(fptr);
            //opens, reads, prints and closes file - end

            break;

        case 2:

            printf("Write your diary entry: \nTo end your entry, type: \"save\" in the next line and press Enter.\n\n");

            //opens, writes, and closes file - start
            fptr = fopen(date, "ab+");

            char entry[1000];
            while(1){
                scanf(" %[^\n]",entry);
                if(!(strcmp(entry,"save")))
                    break;
                else
                    fprintf(fptr,entry);
            }
            fclose(fptr);
            //opens, writes, and closes file - end


            //opens, reads, prints and closes file - start
            fptr = fopen(date, "ab+");
            if(fptr == NULL)
                printf("No such entry\n");
            else
                printf("The entry for %.8s is:\n\n",date);


            reader = fgetc(fptr);
            while (reader != EOF){
                printf ("%c", reader);
                reader = fgetc(fptr);
            }
            printf("\n\n");

            fclose(fptr);
            //opens, reads, prints and closes file - end
            break;
    }

    //fclose(header);
    //fclose(user);
    fclose(fptr);

    return 0;
}

void main_menu(){
    printf("\t\t  __   __  __   __    ______   ___   _______  ______     __   __\n");
    printf("\t _( )_   |  |_|  ||  | |  |  |  _   | |   | |   _   ||    _  \\  |  | |  |    _( )_\n");
    printf("\t(_ o _)  |       ||  |_|  |  | | |   ||   | |  |_|  ||   |_| |  |  |_|  |   (_ o _)\n");
    printf("\t (_-_)   | ||_|| ||_     _|  | |_|   ||   | |       ||    __  \\ |_     _|    (_-_)\n");
    printf("\t\t |_|   |_|  |___|    |______| |___| |__| |__||___|  |_|   |___|\n\n");
    printf("\t      ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~\n\n\n");

}

void addrecord(){
    return 0;
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


