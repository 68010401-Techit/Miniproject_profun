#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';
    
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
    FILE *file = fopen(Data, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }   

    FILE *tempFile = fopen("temp.csv", "w");
    if (tempFile == NULL) {
        printf("Error opening temporary file!\n");
        fclose(file);
        return;
    }
    char searchName[50];
    char Position[50];
    char Phone_number[15];
    char Email[50];
    int found = 0;
    
    printf("Enter the name of the contact to update: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 
   
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", tempName, tempPosition, tempPhone, tempEmail);
       
        if (strcmp(tempName, searchName) == 0) {
            found = 1;
            printf("Enter new Position: ");
            fgets(Position, sizeof(Position), stdin);
            printf("Enter new Phone number: ");
            Position[strcspn(Position, "\n")] = '\0';
            fgets(Phone_number, sizeof(Phone_number), stdin);
            Phone_number[strcspn(Phone_number, "\n")] = '\0';
            printf("Enter new Email: ");
            fgets(Email, sizeof(Email), stdin);
            Email[strcspn(Email, "\n")] = '\0';
            fprintf(tempFile, "%s,%s,%s,%s\n", searchName, Position, Phone_number, Email);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    } else {
        printf("Contact updated successfully!\n");
    }
    
    //เช็คการปิดไฟล์
   if (fclose(file) != 0) {
        printf("Error closing file!\n");
    }
    if (fclose(tempFile) != 0) {
        printf("Error closing temporary file!\n");
    }
    //เช็คการลบและเปลี่ยนชื่อไฟล์
    if (remove(Data) != 0) {
        printf("Error deleting original file!\n");
        return;
    }
    if (rename("temp.csv", Data) != 0) {
        printf("Error renaming temporary file!\n");
    }
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
    while(getchar() != '\n'); //ล้างบัฟเฟอร์
    
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
    
    
