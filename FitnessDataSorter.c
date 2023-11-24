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
                char stepCount[10];
                bool validFile = true;
                //Step through data, tokenise it and store it in the array of fitness data.
                while (fgets(line_buffer, buffer_size, file) != NULL) {
                    tokeniseRecord(line_buffer, ",", data[record].date, data[record].time, stepCount);
                    if(data[record].date == NULL || data[record].time == NULL || stepCount == NULL){
                        validFile = false;
                    }
                    data[record].steps = atoi(stepCount);
                    record++;
                }

                if(validFile){
                    printf("File successfully loaded.\n");
                }
                else{
                    printf("Error: invalid file\n");
                    return 1;
                }
                
                //Close the file.
                fclose(file);
            }
}