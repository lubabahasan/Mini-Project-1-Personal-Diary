#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main()
{
    FILE *header = fopen("My Diary","r");
    FILE *user = fopen("user","r");

    char username[20]="Lubaba";
    char date[10];
    char reader;
    char entry_date;

    int option;

    printf("Hello %s.\nWhat do you want to do?\n1. Read an entry\n2. Make a new entry.\n\nPlease type your preferred option: ",username);
    scanf("%d", &option);

    int select = 1;

    //selects the option - start
    while(select){
        switch (option){
            case 1:
                printf("Which entry do you want to read? (dd.mm.yy)\n");
                select = 0;
                break;
            case 2:
                printf("What's the date today? (dd.mm.yy)\n");
                select = 0;
                break;
            default:
                printf("Please select the correct option.\n");
        }
    }
    //selects the option - end

    scanf("%s", date);     // entries the -.
    strcat(date,".txt");   //               '-> filename
    FILE *fptr;
    fptr = fopen(date, "w"); // opens/creates that file

    //copies contents of template - start
    reader = fgetc(header);
    while (reader != EOF){
        fputc(reader, fptr);
        reader = fgetc(header);
    }
    //copies contents of template - start

    switch(option){
        case 1:
            fptr = fopen(date, "w");
            if(fptr == NULL)
                printf("No such entry\n");

            reader = fgetc(fptr);
            while (reader != EOF){
                printf ("%c", reader);
                reader = fgetc(fptr);
            }

            break;

        case 2:



            printf("Enter date (dd/mm/yyyy): ");
            scanf("%s", entry_date);

            reader = fgetc(fptr);
            while (reader != EOF){
                printf ("%c", fptr);
                reader = fgetc(fptr);
            }

            break;
    }

    fclose(header);
    fclose(user);
    fclose(fptr);
    //fclose(body);

    return 0;
}
