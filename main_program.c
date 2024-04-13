#include <stdio.h>

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
        printf("4. Show percentage of each student\n");
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
                printf("Invalid choic
