#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

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
    printf("Enter filename: ");
    scanf("%s", filename);
            file = fopen(filename, "r");
            if (file == NULL) {
                //Print error message if the file cannot be opened.
                printf("Error: Could not find or open the file.\n");
                return 1;
            }
            else{
                //Declare variables to store data read from the file.
                int buffer_size = 25;
                char line_buffer[buffer_size];
                data = malloc(noOfRecords() * sizeof(FITNESS_DATA));
                int record = 0;
                char stepCount[10];
                //Step through data, tokenise it and store it in the array of fitness data.
                while (fgets(line_buffer, buffer_size, file) != NULL) {
                    tokeniseRecord(line_buffer, ",", data[record].date, data[record].time, stepCount);
                    data[record].steps = atoi(stepCount);
                    record++;
                }
                printf("File successfully loaded.\n");
                //Close the file.
                fclose(file);
            }
}