#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main()
{
    FILE *header = fopen("header","r");
    //FILE *user = fopen("user","r");

    char username[20]="Lubaba";
    char date[10];
    char reader;
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
            fptr = fopen(date, "r");
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
            fptr = fopen(date, "w");

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
            fptr = fopen(date, "r");
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

    fclose(header);
    //fclose(user);
    fclose(fptr);

    return 0;
}
