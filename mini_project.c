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

//ฟังก์ชันแก้ไขข้อมูล
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
    char Position[50], Phone_number[15], Email[50];
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

            int choice;
            printf("choose data you want to update\n");
            printf("1. Position\n");
            printf("2. Phone number\n");
            printf("3. Email\n");
            printf("4. Update all\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            while(getchar() != '\n'); // ล้างบัฟเฟอร์

            switch(choice) {
                case 1:
                    printf("Enter new Position: ");
                    fgets(Position, sizeof(Position), stdin);
                    Position[strcspn(Position, "\n")] = '\0';
                    strcpy(tempPosition, Position);
                    break;
                case 2:
                    printf("Enter new Phone number: ");
                    fgets(Phone_number, sizeof(Phone_number), stdin);
                    Phone_number[strcspn(Phone_number, "\n")] = '\0';
                    strcpy(tempPhone, Phone_number);
                    break;
                case 3:
                    printf("Enter new Email: ");
                    fgets(Email, sizeof(Email), stdin);
                    Email[strcspn(Email, "\n")] = '\0';
                    strcpy(tempEmail, Email);
                    break;
                case 4:
                    printf("Enter new Position: ");
                    fgets(Position, sizeof(Position), stdin);
                    Position[strcspn(Position, "\n")] = '\0';

                    printf("Enter new Phone number: ");
                    fgets(Phone_number, sizeof(Phone_number), stdin);
                    Phone_number[strcspn(Phone_number, "\n")] = '\0';

                    printf("Enter new Email: ");
                    fgets(Email, sizeof(Email), stdin);
                    Email[strcspn(Email, "\n")] = '\0';

                    strcpy(tempPosition, Position);
                    strcpy(tempPhone, Phone_number);
                    strcpy(tempEmail, Email);
                    break;
                default:
                    printf("Invalid choice! Keeping old data.\n");
            }

            fprintf(tempFile, "%s,%s,%s,%s\n", tempName, tempPosition, tempPhone, tempEmail);
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    } else {
        printf("Contact updated successfully!\n");
    }

    fclose(file);
    fclose(tempFile);

    if (remove(Data) != 0) {
        printf("Error deleting original file!\n");
        return;
    }
    if (rename("temp.csv", Data) != 0) {
        printf("Error renaming temporary file!\n");
    }
}

//ฟังก์ชันลบข้อมูล
void delete(const char* Data){
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
    int found = 0;
    
    printf("Enter the name of the contact to delete: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 
   
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", tempName, tempPosition, tempPhone, tempEmail);
       
        if (strcmp(tempName, searchName) == 0) {
            found = 1;
            //ข้ามการเขียนบรรทัดนี้ไปยังไฟล์ชั่วคราว
        } else {
            fprintf(tempFile, "%s", line);
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    } else {
        printf("Contact deleted successfully!\n");
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

//ฟังก์ชันค้นหาข้อมูล
void search(const char* Data){
    FILE *file = fopen(Data, "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }   

    char searchName[50];
    int found = 0;
    
    printf("Enter the name of the contact to search: ");
    fgets(searchName, sizeof(searchName), stdin);
    searchName[strcspn(searchName, "\n")] = '\0'; 
   
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", tempName, tempPosition, tempPhone, tempEmail);
       
        if (strcmp(tempName, searchName) == 0) {
            found = 1;
            printf("Contact found: %s,%s,%s,%s\n", tempName, tempPosition, tempPhone, tempEmail);
            break; // หยุดการค้นหาหลังจากเจอชื่อที่ต้องการ
        }
    }

    if (!found) {
        printf("Contact not found!\n");
    }
    
   if (fclose(file) != 0) {
        printf("Error closing file!\n");
    }
}

//ฟังก์ชันแสดงข้อมูลทั้งหมด
void viewAll(const char* Data) {
    FILE *file = fopen(Data, "r");
    if (file == NULL) {
        printf("No data found.\n");
        return;
    }

    printf("\n===============================================================\n");
    printf("%-20s %-15s %-15s %-20s\n", "Name", "Position", "Phone", "Email");
    printf("===============================================================\n");

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", tempName, tempPosition, tempPhone, tempEmail);
        printf("%-20s %-15s %-15s %-20s\n", tempName, tempPosition, tempPhone, tempEmail);
    }

    printf("===============================================================\n\n");
    fclose(file);

}

//menu
int main() {
    int choice;
    
    do{
    printf("============= Menu =============\n");
    printf("1.add\n");
    printf("2.update\n");
    printf("3.delete\n");
    printf("4.search\n");
    printf("5.view all contact\n");
    printf("6.exit\n");
    printf("================================\n");
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
            delete("data.csv");
            break;
        case 4:
            search("data.csv"); 
            break;
        case 5:
            viewAll("data.csv");
            break;
        case 6:
            printf("Exiting the program.\n");
            break;
        default:
            printf("Error command\n");
            break;
    }
} while(choice != 6);

    return 0;
    }
