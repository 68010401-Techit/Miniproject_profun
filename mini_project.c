#include <stdio.h>
#include <stdlib.h>

//ฟังก์ชันเพิ่มข้อมูล
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

void update(const char* Data){
    FILE *file = fopen(Data, "r+");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }   
    char searchName[50];
    char Position[50];
    char Phone_number[15];
    char Email[50];
    int found = 0;
    printf("Enter the name of the contact to update: ");
    scanf("%s", searchName);
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%s", tempName, tempPosition, tempPhone, tempEmail);
        if (strcmp(tempName, searchName) == 0) {
            found = 1;
            printf("Enter new Position: ");
            scanf("%s", Position);
            printf("Enter new Phone number: ");
            scanf("%s", Phone_number);
            printf("Enter new Email: ");
            scanf("%s", Email);
            fseek(file, -strlen(line), SEEK_CUR);
            fprintf(file, "%s,%s,%s,%s\n", searchName, Position, Phone_number, Email);
            break;
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    } else {
        printf("Contact updated successfully!\n");
    }
    
    fclose(file);
}


//menu
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
            update("data.csv");
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
    
    
