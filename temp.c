#include<stdio.h>
#include<string.h>

void addStudent(FILE *csvFile, int prn, char *name){
    fprintf(csvFile, "%d,%s\n", prn, name);
}

void addAttendance(FILE *csvFile, char *date){
    //Sets the cursor at the start.
    fseek(csvFile, 0, SEEK_SET);


    //Defining an array the store the Header Names.
    char headers[100];
    fgets(headers, sizeof(headers), csvFile);
    printf("%s\n",headers); //Printing all the headers.


    long headersLength = strlen(headers);
    printf("%d\n", headersLength);
    // Move the cursor to the end of the existing headers
    fseek(csvFile, 5, SEEK_SET); // -1 to skip the newline character

    // Add the new date header in the next column
    fprintf(csvFile, ",%s\n", date);
    printf("Date Header Added Successfully.\n");

}

void addnewHeader(FILE *csvFile, char *newHeaders){
    fseek(csvFile, 0, SEEK_SET);

    char existingHeaders[100];
    fgets(existingHeaders, sizeof(existingHeaders), csvFile);

    printf("%s\n", existingHeaders);
    existingHeaders[strcspn(existingHeaders, "\n")] = '\0';


    char combinedHeaders[100];
    strcpy(combinedHeaders, existingHeaders);
    strcat(combinedHeaders, ",");
    strcat(combinedHeaders, newHeaders);

    fseek(csvFile, 0, SEEK_SET);
    fputs(combinedHeaders, csvFile);

    printf("%s\n", combinedHeaders);
}

int main(){
    FILE *csvFile;
    csvFile = fopen("data.csv", "a+");

    if (csvFile == NULL){
        printf("Error opening the file.\n");
        return 1;
    }


    //Checking if the File is Empty.
    fseek(csvFile, 0, SEEK_END);
    long size = ftell(csvFile);

    printf("The size of the file: %d\n", size);

    if(size == 0){
        fprintf(csvFile, "PRN,Name\n");
        printf("File is Empty...Initializing the file.\n");
    }
    else{
        fseek(csvFile, 0, SEEK_END);
        printf("File is populated.\n");
    }
    //Adding Students in the csv file.

    //addStudent(csvFile, 101, "Aryan Mallick");
    //addStudent(csvFile, 102, "Rajvir Singh Chadda");


   //addAttendance(csvFile, "11/04/24");
    
    addnewHeader(csvFile, "11/04/24");
    addnewHeader(csvFile, "12/04/24");
    addnewHeader(csvFile, "13/04/24");
    
    fclose(csvFile);
    printf("Headers are written successfully.\n");
    return 0;
}