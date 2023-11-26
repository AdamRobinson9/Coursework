#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

FILE *file;
FitnessData *data;
int noOfRecords = 0;

// Function to tokenize a record
void tokeniseRecord(char *record, char delimiter, char *date, char *time, int *steps) {
    char *ptr = strtok(record, &delimiter);
    if (ptr != NULL) {
        strcpy(date, ptr);
        ptr = strtok(NULL, &delimiter);
        if (ptr != NULL) {
            strcpy(time, ptr);
            ptr = strtok(NULL, &delimiter);
            if (ptr != NULL) {
                *steps = atoi(ptr);
            }
        }
    }
}

int main() {
    char filename[100];
    printf("Input filename: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        //Print error message if the file cannot be opened.
        printf("Error: invalid file\n");
            return 1;
    }
    else{
        //Declare variables to store data read from the file.
        int buffer_size = 25;
        char line_buffer[buffer_size];
        while (fgets(line_buffer, buffer_size, file) != NULL) {
            noOfRecords++;
        }
        data = malloc(noOfRecords * sizeof(FitnessData));
                
        rewind(file);

        int record = 0;
        //Step through data, tokenise it and store it in the array of fitness data.
        while (fgets(line_buffer, buffer_size, file) != NULL) {
            tokeniseRecord(line_buffer, ',', data[record].date, data[record].time, &data[record].steps);
            record++;
        }
                
        bool invalidData = false;
        for (int i=0; i<noOfRecords; i++){
            if(strlen(data[i].date) != 10 || strlen(data[i].time) != 5 || data[i].time < 0){
                invalidData = true;
            }
        }

        if (invalidData){
            printf("Error: invalid file\n");
            return 1;
        }
        else{
            for (int i=0; i<noOfRecords; i++){
                printf("%s\t%s\t%d\n", data[i].date, data[i].time, data[i].steps);
            }
        }
    }
    //Close the file.
    fclose(file);
}