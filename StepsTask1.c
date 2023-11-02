#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Fitness data struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

//Method to count the number of items in the csv file.
int noOfRecords(){
    //Open the file in read mode.
    char* filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    //Initialise buffer and variable to count the number of entries.
    int buffer_size = 25;
    char line_buffer[buffer_size];
    int count = 0;

    //Increment the counter each time the 
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        count++;
    }
    //Return number of items in the file.
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
    //Open the file in read mode.
    char* filename = "FitnessData_2023.csv";
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    //Declare the buffer and variables to store data from the file.
    int buffer_size = 25;
    char line_buffer[buffer_size];
    FITNESS_DATA data[noOfRecords()];
    int record = 0;
    char stepCount[10];

    //Step through data, tokenise it and store it in the array of fitness data.
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        tokeniseRecord(line_buffer, ",", data[record].date, data[record].time, stepCount);
        data[record].steps = atoi(stepCount);
        record++;
    }

    //Print the number of records.
    printf("Number of records in file: %d\n", noOfRecords());

    //Print the first 3 lines in the data.
    for (int i=0; i<3; i++){
        printf("%s/%s/%d\n", data[i].date, data[i].time, data[i].steps);
    }

    //Close the file.
    fclose(file);
    
    return 0;
}