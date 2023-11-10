#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
FILE *file;


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


int optionB(){
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

FITNESS_DATA optionC(){
    int buffer_size = 25;
    char line_buffer[buffer_size];
    FITNESS_DATA data[60];
    int record = 0;
    char stepCount[10];

    //Step through data, tokenise it and store it in the array of fitness data.
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        tokeniseRecord(line_buffer, ",", data[record].date, data[record].time, stepCount);
        data[record].steps = atoi(stepCount);
        record++;
    }

    FITNESS_DATA fewestSteps;
    
    for (int i = 0; i < record; i++){
        if(i==0){
            fewestSteps = data[i];
        }
        else{
            if(data[i].steps < fewestSteps.steps){
                fewestSteps = data[i];
            }
        }
    }
    return fewestSteps;
}

// Complete the main function
int main() {
    bool endProcess = false;
    char filename[100];
    while(!endProcess){
        printf("Menu Options:\n"
                "A: Specify the filename to be imported\n"
                "B: Display the total number of records in the file\n"
                "C: Find the date and time of the timeslot with the fewest steps\n"
                "D: Find the date and time of the timeslot with the largest number of steps\n"
                "E: Find the mean step count of all the records in the file\n"
                "F: Find the longest continuous period where the step count is above 500 steps\n"
                "Q: Quit\n");

        char option;
        scanf (" %c", &option);


        switch (option) {
        case 'A':
            //Open the file in read mode.
            printf("Input filename: ");
            scanf("%s", filename);
            file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error: Could not find or open the file.\n");
                return 1;
            }
            else{
                printf("File successfully loaded.\n");
            }
            break;
        case 'B':
            printf("Total records: %d\n", optionB());
            rewind(file);
            break;
        case 'C':
            printf("Fewest steps: %d\n", optionC().steps);
            rewind(file);
            break;
        case 'D':
            //code
            break;
        case 'E':
            //code
            break;
        case 'F':
            //code
            break;
        case 'Q':
            //Close the file.
            fclose(file);
            
            return 0;
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }    
    return 0;
}