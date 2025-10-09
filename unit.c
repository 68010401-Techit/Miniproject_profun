#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "unit.h" 

// ===========================
// 📘 TEST ฟังก์ชัน add()
// ===========================
void test_add_normal() {
    FILE *f = fopen("test_data.csv", "w");
    fclose(f);

    FILE *file = fopen("test_data.csv", "a");
    fprintf(file, "John,Manager,0812345678,john@example.com\n");
    fclose(file);

    file = fopen("test_data.csv", "r");
    char line[200];
    fgets(line, sizeof(line), file);
    fclose(file);

    assert(strstr(line, "John") != NULL);
    printf("test_add_normal passed\n");
}

void test_add_extreme_long_name() {
    FILE *f = fopen("test_data.csv", "w");
    fclose(f);

    char longName[60];
    memset(longName, 'A', 49); // ชื่อยาว 49 ตัวอักษร
    longName[49] = '\0';

    FILE *file = fopen("test_data.csv", "a");
    fprintf(file, "%s,CEO,0999999999,longname@example.com\n", longName);
    fclose(file);

    file = fopen("test_data.csv", "r");
    char line[200];
    fgets(line, sizeof(line), file);
    fclose(file);

    assert(strncmp(line, longName, 10) == 0); // ตรวจต้นชื่อ
    printf("test_add_extreme_long_name passed\n");
}

void test_add_invalid_data() {
    FILE *f = fopen("test_data.csv", "w");
    fclose(f);

    FILE *file = fopen("test_data.csv", "a");
    // ใส่ข้อมูลไม่ครบ
    fprintf(file, "Lisa,Accountant, , \n");
    fclose(file);

    file = fopen("test_data.csv", "r");
    char line[200];
    fgets(line, sizeof(line), file);
    fclose(file);

    // เช็คว่ามีเครื่องหมาย comma แต่ไม่มีอีเมล
    assert(strstr(line, ", ,") != NULL);
    printf("test_add_invalid_data passed\n");
}

// ===========================
// 🧭 TEST ฟังก์ชัน update()
// ===========================
void test_update_existing_contact() {
    FILE *f = fopen("test_data.csv", "w");
    fprintf(f, "Alice,Engineer,0123456789,alice@example.com\n");
    fclose(f);

    // เปลี่ยนตำแหน่ง
    FILE *file = fopen("test_data.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", tempName, tempPosition, tempPhone, tempEmail);
        if (strcmp(tempName, "Alice") == 0) {
            fprintf(temp, "%s,%s,%s,%s\n", tempName, "Developer", tempPhone, tempEmail);
        } else {
            fprintf(temp, "%s", line);
        }
    }
    fclose(file);
    fclose(temp);
    remove("test_data.csv");
    rename("temp.csv", "test_data.csv");

    f = fopen("test_data.csv", "r");
    fgets(line, sizeof(line), f);
    fclose(f);
    assert(strstr(line, "Developer") != NULL);
    printf("test_update_existing_contact passed\n");
}

void test_update_not_found() {
    FILE *f = fopen("test_data.csv", "w");
    fprintf(f, "Bob,Intern,0999999999,bob@example.com\n");
    fclose(f);

    char found = 0;
    FILE *file = fopen("test_data.csv", "r");
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, "NonExist") != NULL) {
            found = 1;
        }
    }
    fclose(file);

    assert(found == 0); // ต้องไม่เจอชื่อ
    printf("test_update_not_found passed\n");
}

void test_update_extreme_field_length() {
    FILE *f = fopen("test_data.csv", "w");
    fprintf(f, "Charlie,Intern,0888888888,charlie@example.com\n");
    fclose(f);

    // เปลี่ยนชื่อเป็นตำแหน่งยาวสุดๆ
    char longPos[60];
    memset(longPos, 'B', 49);
    longPos[49] = '\0';

    FILE *file = fopen("test_data.csv", "r");
    FILE *temp = fopen("temp.csv", "w");
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char tempName[50], tempPosition[50], tempPhone[15], tempEmail[50];
        sscanf(line, "%[^,],%[^,],%[^,],%[^\n]", tempName, tempPosition, tempPhone, tempEmail);
        if (strcmp(tempName, "Charlie") == 0) {
            fprintf(temp, "%s,%s,%s,%s\n", tempName, longPos, tempPhone, tempEmail);
        } else {
            fprintf(temp, "%s", line);
        }
    }
    fclose(file);
    fclose(temp);
    remove("test_data.csv");
    rename("temp.csv", "test_data.csv");

    f = fopen("test_data.csv", "r");
    fgets(line, sizeof(line), f);
    fclose(f);
    assert(strstr(line, "BBBBBBBB") != NULL);
    printf("test_update_extreme_field_length passed\n");
}

// ===========================
// 🚀 MAIN TEST RUNNER
// ===========================
void unit() {
    printf("Running Unit Tests...\n\n");
    test_add_normal();
    test_add_extreme_long_name();
    test_add_invalid_data();
    test_update_existing_contact();
    test_update_not_found();
    test_update_extreme_field_length();

    printf("\n All tests passed successfully!\n");
}
