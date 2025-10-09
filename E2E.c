#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "E2E.h" 

void add_contact(const char* Data) {
    FILE *file = fopen(Data, "a");
    if (!file) { printf("Error opening file!\n"); return; }

    char name[50], Position[50], Phone_number[15], Email[50];
    char cont;

    do {
        printf("Enter Contact Name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = '\0';

        printf("Enter Position: ");
        fgets(Position, sizeof(Position), stdin);
        Position[strcspn(Position, "\n")] = '\0';

        printf("Enter Phone number: ");
        fgets(Phone_number, sizeof(Phone_number), stdin);
        Phone_number[strcspn(Phone_number, "\n")] = '\0';

        printf("Enter Email: ");
        fgets(Email, sizeof(Email), stdin);
        Email[strcspn(Email, "\n")] = '\0';

        fprintf(file, "%s,%s,%s,%s\n", name, Position, Phone_number, Email);
        printf("Contact added successfully!\n");

        printf("Add another contact? (y/n): ");
        cont = getchar();
        while (getchar() != '\n');
    } while (cont == 'y' || cont == 'Y');

    fclose(file);
}

void update_contact(const char* Data) {
    char cont;

    do {
        FILE *file = fopen(Data, "r");
        if (!file) { printf("Error opening file!\n"); return; }

        FILE *tempFile = fopen("temp.csv", "w");
        if (!tempFile) { printf("Error opening temp file!\n"); fclose(file); return; }

        char searchName[50], Position[50], Phone_number[15], Email[50];
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
                printf("Choose data to update:\n1. Position\n2. Phone number\n3. Email\n4. All\nEnter choice: ");
                scanf("%d", &choice);
                while (getchar() != '\n');

                if (choice == 1 || choice == 4) {
                    printf("Enter new Position: ");
                    fgets(Position, sizeof(Position), stdin);
                    Position[strcspn(Position, "\n")] = '\0';
                    strcpy(tempPosition, Position);
                }
                if (choice == 2 || choice == 4) {
                    printf("Enter new Phone number: ");
                    fgets(Phone_number, sizeof(Phone_number), stdin);
                    Phone_number[strcspn(Phone_number, "\n")] = '\0';
                    strcpy(tempPhone, Phone_number);
                }
                if (choice == 3 || choice == 4) {
                    printf("Enter new Email: ");
                    fgets(Email, sizeof(Email), stdin);
                    Email[strcspn(Email, "\n")] = '\0';
                    strcpy(tempEmail, Email);
                }

                printf("Contact updated successfully!\n");
            }

            fprintf(tempFile, "%s,%s,%s,%s\n", tempName, tempPosition, tempPhone, tempEmail);
        }

        if (!found) printf("Contact not found!\n");

        fclose(file);
        fclose(tempFile);
        remove(Data);
        rename("temp.csv", Data);

        printf("Update another contact? (y/n): ");
        cont = getchar();
        while (getchar() != '\n');

    } while (cont == 'y' || cont == 'Y');
}

void delete_contact(const char* Data) {
    char cont;

    do {
        FILE *file = fopen(Data, "r");
        if (!file) { printf("Error opening file!\n"); return; }

        FILE *tempFile = fopen("temp.csv", "w");
        if (!tempFile) { printf("Error opening temp file!\n"); fclose(file); return; }

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
                printf("Contact deleted successfully!\n");
            } else {
                fprintf(tempFile, "%s", line);
            }
        }

        if (!found) printf("Contact not found!\n");

        fclose(file);
        fclose(tempFile);
        remove(Data);
        rename("temp.csv", Data);

        printf("Delete another contact? (y/n): ");
        cont = getchar();
        while (getchar() != '\n');

    } while (cont == 'y' || cont == 'Y');
}

void search_contact(const char* Data) {
    char cont;

    do {
        FILE *file = fopen(Data, "r");
        if (!file) { printf("Error opening file!\n"); return; }

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
                printf("Contact found: %s,%s,%s,%s\n", tempName, tempPosition, tempPhone, tempEmail);
                found = 1;
                break;
            }
        }

        if (!found) printf("Contact not found!\n");
        fclose(file);

        printf("Search another contact? (y/n): ");
        cont = getchar();
        while (getchar() != '\n');
    } while (cont == 'y' || cont == 'Y');
}

void viewAll_contact(const char* Data) { // ต้องใช้ตัวใหญ่ให้ตรงกับ E2E()
    FILE *file = fopen(Data, "r");
    if (!file) { printf("No data found.\n"); return; }

    printf("\n================================================================================\n");
    printf("%-20s %-15s %-15s %-20s\n", "Name", "Position", "Phone", "Email");
    printf("================================================================================\n");

    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", tempName, tempPosition, tempPhone, tempEmail);
        printf("%-20s %-15s %-15s %-20s\n", tempName, tempPosition, tempPhone, tempEmail);
    }

    printf("===============================================================================\n\n");
    fclose(file);
}

void E2E() {
    printf("\n=== Running End-to-End Test ===\n");

    printf("Adding 2 test contacts...\n");
    add_contact("test_data.csv");
    viewAll_contact("test_data.csv");

    printf("Updating a contact...\n");
    update_contact("test_data.csv");

    printf("Deleting a contact...\n");
    delete_contact("test_data.csv");

    printf("Searching a contact...\n");
    search_contact("test_data.csv");

    printf("End-to-End Test Completed.\n");
}
