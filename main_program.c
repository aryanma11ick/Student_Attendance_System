#include <stdio.h>
#include <string.h>

// Define a structure for student data
struct Student {
    int rollNo;
    char name[50];
    int numAttendances;
    int numPresent;
};

// Function prototypes
void registerStudent(struct Student students[], int *numStudents);
void markAttendance(struct Student students[], int numStudents);
void editAttendance(struct Student students[], int numStudents);
void showPercentage(struct Student students[], int numStudents);

int main() {
    struct Student students[100];  // Assuming maximum 100 students
    int numStudents = 0;
    int choice;

    do {
        // Display menu options
        printf("\nMenu:\n");
        printf("1. Register new student\n");
        printf("2. Mark attendance\n");
        printf("3. Edit attendance\n");
        printf("4. Show percentage of attendance\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                registerStudent(students, &numStudents);
                break;
            case 2:
                markAttendance(students, numStudents);
                break;
            case 3:
                editAttendance(students, numStudents);
                break;
            case 4:
                showPercentage(students, numStudents);
                break;
            case 0:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 0);

    return 0;
}

void registerStudent(struct Student students[], int *numStudents) {
    if (*numStudents < 100) {
        printf("Enter student full name: ");
        scanf("  %[^\n]", students[*numStudents].name);  // Read full name until newline

        printf("Enter student roll number: ");
        scanf("%d", &students[*numStudents].rollNo);

        students[*numStudents].numAttendances = 0;
        students[*numStudents].numPresent = 0;

        (*numStudents)++;
        printf("Student registered successfully.\n");
    } else {
        printf("Maximum number of students reached.\n");
    }
}

void markAttendance(struct Student students[], int numStudents) {
    char date[10];  // Date in DD/MM/YY format

    printf("Enter date in DD/MM/YY format: ");
    scanf("%s", date);

    FILE *fp;
    fp = fopen("attendance.csv", "a");  // Open the file in append mode

    if (fp == NULL) {
        printf("Error opening file for appending!\n");
        return;
    }

    // Write headers if the file is empty
    fseek(fp, 0, SEEK_END);  // Move to end of file
    if (ftell(fp) == 0) {  // Check if file is empty
        fprintf(fp, "Roll No,Name,%s\n", date);  // Write headers
    }

    // Prompt user for attendance and write to file
    for (int i = 0; i < numStudents; i++) {
        char attendance;
        printf("Enter attendance for %s (P or A): ", students[i].name);
        scanf(" %c", &attendance);  // Assuming single character input (P or A)

        fprintf(fp, "%d,%s,%c\n", students[i].rollNo, students[i].name, attendance);
    }

    // Close the file
    fclose(fp);
    printf("Attendance marked successfully.\n");
}

void editAttendance(struct Student students[], int numStudents) {
    int rollNo;
    printf("Enter student roll number to edit attendance: ");
    scanf("%d", &rollNo);

    for (int i = 0; i < numStudents; i++) {
        if (students[i].rollNo == rollNo) {
            char attendance;
            printf("Enter updated attendance for %s (P or A): ", students[i].name);
            scanf(" %c", &attendance);  // Assuming single character input (P or A)

            if (attendance == 'P') {
                students[i].numPresent++;
            }

            printf("Attendance updated successfully for %s.\n", students[i].name);
            return;
        }
    }

    printf("Student with roll number %d not found.\n", rollNo);
}

void showPercentage(struct Student students[], int numStudents) {
    int rollNo;
    printf("Enter student roll number to calculate attendance percentage: ");
    scanf("%d", &rollNo);

    int totalEntries = 0;
    int presentEntries = 0;

    FILE *fp = fopen("attendance.csv", "r");
    if (fp == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    // Read the header line
    char header[100];
    fgets(header, sizeof(header), fp);

    // Read each line and search for the specified roll number
    char line[100];
    while (fgets(line, sizeof(line), fp)) {
        int studentRollNo;
        char name[50];
        char attendance;

        // Parse the line to extract roll number, name, and attendance
        sscanf(line, "%d,%[^,],%c", &studentRollNo, name, &attendance);

        if (studentRollNo == rollNo) {
            totalEntries++;
            if (attendance == 'P') {
                presentEntries++;
            }
        }
    }

    // Close the file
    fclose(fp);

    // Calculate and display percentage
    float percentage = 0.0;
    if (totalEntries > 0) {
        percentage = (float)presentEntries / totalEntries * 100;
    }

    printf("Attendance percentage for student with roll number %d: %.2f%%\n", rollNo, percentage);
}
