#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here

int noOfRecords(){
     char* filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int buffer_size = 25;
    char line_buffer[buffer_size];
    int count = 0;

    while (fgets(line_buffer, buffer_size, file) != NULL) {
        count++;
    }
    return count;
}

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter,
                    char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);

}

// Complete the main function
int main() {
    char* filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    int buffer_size = 25;
    char line_buffer[buffer_size];

    FITNESS_DATA data[noOfRecords()];
    int record = 0;
    char stepCount[10];

    while (fgets(line_buffer, buffer_size, file) != NULL) {
        tokeniseRecord(line_buffer, ",", data[record].date, data[record].time, stepCount);
        data[record].steps = atoi(stepCount);
        record++;
    }

    printf("Number of records in file: %d\n", noOfRecords());

    for (int i=0; i<3; i++){
        printf("%s/%s/%d\n", data[i].date, data[i].time, data[i].steps);
    }

    fclose(file);
    return 0;
}