#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char name[50];
    int rollNumber;
    char date[11]; // DD/MM/YYYY format
    int attendance[5]; // Attendance for 5 days
};

void inputAttendance(struct Student *student, int numDays) {
    printf("Enter attendance for %s (Roll Number: %d) for each day (0 for absent, 1 for present):\n", student->name, student->rollNumber);
    printf("Enter date (DD/MM/YYYY): ");
    scanf("%10s", student->date);
    for (int i = 0; i < numDays; i++) {
        printf("Day %d: ", i + 1);
        scanf("%d", &student->attendance[i]);
    }
}

void calculatePercentage(struct Student *student, int numDays) {
    int totalDays = 0, presentDays = 0;
    for (int i = 0; i < numDays; i++) {
        totalDays++;
        if (student->attendance[i] == 1) {
            presentDays++;
        }
    }
    float percentage = (float)presentDays / totalDays * 100.0;
    printf("%s (Roll Number: %d) Attendance Percentage: %.2f%%\n", student->name, student->rollNumber, percentage);
}

void writeToCSV(struct Student students[], int numStudents, int numDays) {
    FILE *fp;
    fp = fopen("attendance.csv", "w");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(fp, "Name,Roll Number,Date,Day 1,Day 2,Day 3,Day 4,Day 5\n");
    for (int i = 0; i < numStudents; i++) {
        fprintf(fp, "%s,%d,%s", students[i].name, students[i].rollNumber, students[i].date);
        for (int j = 0; j < numDays; j++) {
            fprintf(fp, ",%d", students[i].attendance[j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}

void readFromCSV() {
    FILE *fp;
    char line[200];
    fp = fopen("attendance.csv", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }
    printf("Reading attendance data from CSV:\n");
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }
    fclose(fp);
}

int main() {
    struct Student students[3]; // Adjust size as needed
    int numDays = 5;

    strcpy(students[0].name, "John");
    students[0].rollNumber = 101;
    inputAttendance(&students[0], numDays);
    calculatePercentage(&students[0], numDays);

    strcpy(students[1].name, "Jane");
    students[1].rollNumber = 102;
    inputAttendance(&students[1], numDays);
    calculatePercentage(&students[1], numDays);

    strcpy(students[2].name, "Doe");
    students[2].rollNumber = 103;
    inputAttendance(&students[2], numDays);
    calculatePercentage(&students[2], numDays);

    // Write data to CSV
    writeToCSV(students, 3, numDays);

    // Read data from CSV
    readFromCSV();

    return 0;
}
