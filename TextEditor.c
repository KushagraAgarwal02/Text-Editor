#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create();
void entertxt();
void display();
void merge();
void status();
void find();
void print_status();
void open();
void edit();

FILE *file;
char filename[20];
int ch;
int lines = 1, words = 0, characters = 0, paragraphs = 1;
char text[1000];

int main() {
    int choice;

    printf("\n\n\t\t*************************************************************
WELCOME ********************************************************");

    do {
        printf("\n\n\tMENU:\n\n ");
        printf("\n\t1.CREATE\n\t2.OPEN\n\t3.MERGE\n\t4.STATUS\n\t5.FIND\n\t0.EXIT\n");
        printf("\n\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                create();
                break;
            case 2:
                open();
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
                printf("\n\n\t\t\t\t\t********************************EXITING THE 
PROGRAM.********************************");
                exit(0);
                break;
            default:
                printf("Error! Input is not correct.\n");
        }
    } while (1);
}

void create() {
    int choice;
    printf("\nENTER FILE NAME and its .extension: ");
    scanf("%s", filename);
    file = fopen(filename, "w+");
    if (file != NULL) {
        printf("File %s created successfully.\n", filename);
        do {
            printf("\nENTER OPERATION FROM THE FOLLOWING:");
            printf("\n1. EDIT\n2. DISPLAY\n0. EXIT\n");
            printf("\nENTER YOUR CHOICE: ");
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    entertxt();
                    break;
                case 2:
                    display(filename);
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

void entertxt() {
    file = fopen(filename, "a+");
    printf("Enter text (type 'END' on a new line to save and exit):\n");
    while (fgets(text, sizeof(text), stdin)) {
        if (strcmp(text, "END\n") == 0) {
            break;
        }
        fputs(text, file);
    }
    fclose(file);
}

void display(char n[20]) {
    file = fopen(n, "r");
    if (file == NULL) {
        printf("ERROR\n");
        return;
    }
    printf("FILENAME: %s\nTEXT:\n", n);
    char text[1000];
    while (fgets(text, sizeof(text), file)) {
        printf("%s", text);
    }
    fclose(file);
}

void status() {
    printf("Enter file name: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s", filename);
        return;
    }
    int last_char_was_space = 1;
    int last_char_was_newline = 1;
    int last_char_was_word = 0;
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
            if (last_char_was_word) {
                words++;
                last_char_was_word = 0;
            }
        } else {
            last_char_was_space = 0;
            last_char_was_word = 1;
        }
    }
    if (last_char_was_word) {
        words++;
    }
    if (characters > 0) {
        lines++;
    }
    print_status();
}

void print_status() {
    printf("Lines: %d\n", lines);
    printf("Words: %d\n");
    printf("Paragraphs: %d\n", paragraphs);
}

void merge() {
    FILE *file1, *file2, *file3;
    char ch, f1[20], f2[20], f3[20];
    printf("Enter name of file 1:");
    scanf("%s", f1);
    file1 = fopen(f1, "r");
    if (file1 == NULL) {
        printf("Cannot open %s\n", f1);
        return;
    }
    printf("Enter name of file 2:");
    scanf("%s", f2);
    file2 = fopen(f2, "r");
    if (file2 == NULL) {
        printf("Cannot open %s\n", f2);
        return;
    }
    printf("Enter name of file 3:");
    scanf("%s", f3);
    file3 = fopen(f3, "w");
    if (file3 == NULL) {
        printf("Cannot open %s\n", f3);
        return;
    }
    while ((ch = fgetc(file1)) != EOF)
        fputc(ch, file3);
    while ((ch = fgetc(file2)) != EOF)
        fputc(ch, file3);
    printf("\t\t\t\t\t\t\t\t\tMERGE COMPLETE!\n\n");
    fclose(file1);
    fclose(file2);
    fclose(file3);
    display(f3);
}

void find() {
    char find[1000];
    printf("CASE SHOULD MATCH!\n");
    printf("FIND: ");
    scanf("%s", find);
    printf("\nEnter file name: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Could not open file %s", filename);
        return;
    }
    int found = 0;
    int line_number = 1;
    while (fgets(text, sizeof(text), file)) {
        line_number++;
        if (strstr(text, find) != NULL) {
            printf("\nTEXT: %s FOUND AT Line %d:\n", find - 1, line_number - 1);
            found = 1;
        }
    }
    if (!found) {
        printf("\nTEXT NOT FOUND!");
    }
    fclose(file);
}

void open() {
    char nameoffile[20];
    printf("NAME OF FILE TO OPEN:");
    scanf("%s", nameoffile);
    file = fopen(nameoffile, "r+");
    if (file == NULL) {
        printf("ERROR! FILE DOES NOT EXIST!\n");
        return;
    }
    printf("FILENAME: %s\nTEXT:\n", nameoffile);
    while (fgets(text, sizeof(text), file)) {
        printf("%s", text);
    }
}

