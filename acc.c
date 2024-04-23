#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_DATE_LENGTH 20
#define CSV_FILE "attendance.csv"

struct Student {
    int prn;
    char name[50];
    int attendance[MAX_DATE_LENGTH]; // Assuming attendance is marked as 0 (absent) or 1 (present)
};

struct Student students[MAX_STUDENTS];
int numStudents = 0;
char dates[MAX_DATE_LENGTH][20]; // Store date headers

void loadDatesFromFile() {
    FILE *file = fopen(CSV_FILE, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fscanf(file, "PRN,Name");
    while (fscanf(file, ",%19[^,\n]", dates[numStudents]) != EOF) {
        numStudents++;
    }
    fclose(file);
}

void registerStudent() {
    if (numStudents >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }
    printf("Enter PRN: ");
    scanf("%d", &students[numStudents].prn);
    printf("Enter Name: ");
    scanf(" %[^\n]", students[numStudents].name);
    numStudents++;
}

void markAttendance() {
    int prn, present;
    printf("Enter PRN: ");
    scanf("%d", &prn);
    for (int i = 0; i < numStudents; i++) {
        if (students[i].prn == prn) {
            printf("Enter 1 for present, 0 for absent: ");
            scanf("%d", &present);
            // Adjust index to numStudents - 1 since numStudents increments after adding a student
            students[i].attendance[numStudents - 1] = present;
            printf("Attendance marked for %s.\n", students[i].name);
            return;
        }
    }
    printf("Student not found.\n");
}

void saveAttendanceToFile() {
    FILE *file = fopen(CSV_FILE, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "PRN,Name");
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, ",%s", students[i].name);
    }
    fprintf(file, "\n");
    fprintf(file, ","); // Skip PRN column for date headers
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, ",%s", dates[i]);
    }
    fprintf(file, "\n");
    for (int i = 0; i < MAX_DATE_LENGTH; i++) {
        fprintf(file, "%s", dates[i]);
        for (int j = 0; j < numStudents; j++) {
            fprintf(file, ",%d", students[j].attendance[i]);
        }
        fprintf(file, "\n");
    }
    fclose(file);
}

void calculateAttendance() {
    for (int i = 0; i < numStudents; i++) {
        int presentCount = 0;
        for (int j = 0; j < MAX_DATE_LENGTH; j++) {
            presentCount += students[i].attendance[j];
        }
        float attendancePercentage = (float)presentCount / MAX_DATE_LENGTH * 100.0;
        printf("Attendance Percentage for %s: %.2f%%\n", students[i].name, attendancePercentage);
    }
}

int main() {
    loadDatesFromFile();

    int choice;
    do {
        printf("\nAttendance Tracker Menu:\n");
        printf("1. Register Student\n");
        printf("2. Mark Attendance\n");
        printf("3. Save Attendance to File\n");
        printf("4. Calculate Attendance Percentage\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerStudent();
                break;
            case 2:
                markAttendance();
                break;
            case 3:
                saveAttendanceToFile();
                break;
            case 4:
                calculateAttendance();
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}