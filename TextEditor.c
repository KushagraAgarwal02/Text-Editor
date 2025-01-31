// Text Editor

#include <stdio.h>
#include <stdlib.h>
#include<string.h>

// Global functions and variables
FILE *file;
char filename[20];
void create();
void edit();
void display();
void merge();
void status();
void find();


int main() {
    int choice;
    printf("\n\t\t\t\t\t\t\t\t\t\t\t***** TEXT EDITOR *****");
    do {
        printf("\n\n\tMENU:\n\n ");
        printf("\n\t1.CREATE\n\t2.DISPLAY\n\t3.MERGE\n\t4.STATUS\n\t5.FIND\n\t0.EXIT\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                display();
                break;
            case 3:
                merge();
                break;
            case 4:
                status();
                break;
            case 5:
                find();
                break;
            case 0:
                printf("Exiting the program.\n");
                exit(0);
                break;
            default:
                printf("Error! Input is not correct.\n");
        }
    } while (1);
}

void create() {
    int choice;
    // create()
    printf("\nENTER FILE NAME and its .extension: ");
    scanf("%s", filename);
    file = fopen(filename, "w+");

    if (file != NULL) {
        printf("File %s created successfully.\n", filename);

        do {
            // Sub-Menu
            printf("\nENTER OPERATION FROM THE FOLLOWING:");
            printf("\n1. EDIT\n2. DISPLAY\n0. EXIT\n");
            printf("\nENTER YOUR CHOICE: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    edit();
                    break;
                case 2:
                    display();
                    break;
                case 0:
                    break;
                default:
                    printf("INCORRECT CHOICE!\n");
            }
        } while (choice != 0);

        fclose(file);
    } else {
        printf("Error opening the file.\n");
    }
}

void edit() {
    char text[1000];
    file = fopen(filename, "a+");  // Open the file in append mode
    printf("Enter text (type 'END' on a new line to save and exit):\n");

    while (fgets(text, sizeof(text), stdin)) {
        if (strcmp(text, "END\n") == 0) {
            break;  // Exit the input loop when "END" is entered
        }
        fputs(text, file);
    }

    fclose(file);  // Close the file after editing
}


void display() {
    file = fopen(filename, "r");  // Open the file in read mode
    if (file == NULL) {
        printf("ERROR\n");
        return;
    }

    printf("FILENAME: %s\nTEXT:\n", filename);
    
    char text[1000];
    while (fgets(text, sizeof(text), file)) {
        printf("%s", text);  // Display each line of the file
    }

    fclose(file);
}

void status(){
    FILE *file;
    char filename[100];
    char ch;
    int lines = 0, words = 0, characters = 0, paragraphs = 0;
    int last_char_was_space = 1;
    int last_char_was_newline = 1;
    // Input path of files to count lines and words
    printf("Enter file name: ");
    scanf("%s", filename);

    // Open file
    file = fopen(filename, "r");

    // Check if file exists
    if (file == NULL) {
        printf("Could not open file %s", filename);
        return;
    }

    // Extract characters from file and count lines, words and characters
    while ((ch = fgetc(file)) != EOF) {
        characters++;

        if (ch == '\n') {
            lines++;
            if (last_char_was_newline) {
                paragraphs++;
            }
            last_char_was_newline = 1;
        } else {
            last_char_was_newline = 0;
        }

        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
            last_char_was_space = 1;
        } else if (last_char_was_space) {
            words++;
            last_char_was_space = 0;
        }
    }

    fclose(file);

    printf("Lines: %d\n", lines+1);
    printf("Words: %d\n", words);
    printf("Characters: %d\n", characters);
    printf("Paragraphs: %d\n", paragraphs);

}

void merge(){
    FILE *file1, *file2, *file3;
    char ch,f1[10],f2[10],f3[10];

    // Open first file for reading
    printf("Enter name of file 1:");
    scanf("%s",f1);
    file1 = fopen(f1, "r");
    if (file1 == NULL) {
        printf("Cannot open file1.txt\n");
        return;
    }

    // Open second file for reading
    printf("Enter name of file you want to merge:");
    scanf("%s",f2);
    file2 = fopen(f2, "r");
    if (file2 == NULL) {
        printf("Cannot open file2.txt\n");
        return;
    }

    // Open third file for writing
    printf("Enter name of file 3:");
    scanf("%s",f3);
    file3 = fopen(f3, "w");
    if (file3 == NULL) {
        printf("Cannot open file3.txt\n");
        return;
    }

    // Read contents from first file and write to third file
    while ((ch = fgetc(file1)) != EOF)
        fputc(ch, file3);

    // Read contents from second file and write to third file
    while ((ch = fgetc(file2)) != EOF)
        fputc(ch, file3);

    printf("Merged file1.txt and file2.txt into file3.txt\n");

    // Close all files
    fclose(file1);
    fclose(file2);
    fclose(file3);
}

void find(){
    
}

