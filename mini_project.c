#include <stdio.h>
#include <stdlib.h>

void add(const char* Data){
    FILE *file = fopen(Data, "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    
    char name[50];
    char Position[50];
    char Phone_number[15];
    char Email[50];
    
    printf("Enter ContactName: ");
    scanf("%s", name);
    printf("Enter Position: ");
    scanf("%s", Position);
    printf("Enter Phone number: ");
    scanf("%s", Phone_number);
    printf("Enter Email: ");
    scanf("%s", Email);
    
    fprintf(file, "%s,%s,%s,%s\n", name, Position, Phone_number, Email);
    
    fclose(file);
    
    printf("Contact added successfully!\n");
}


int main() {
    int choice;
    
    do{
        printf("Menu\n");
    printf("1.add\n");
    printf("2.update\n");
    printf("3.delete\n");
    printf("4.search\n");
    printf("5.exit\n");
    
    printf("Enter your choice: ");
    scanf("%d", &choice);
    
    switch(choice) {
        case 1:
            add("data.csv");
            break;
        case 2:
            printf("Update function called\n");
            break;
        case 3:
            printf("Delete function called\n");
            break;
        case 4:
            printf("Search function called\n"); 
            break;
        case 5:
            printf("Exiting the program.\n");
    }
} while(choice != 5);

    return 0;
    }
    
    
