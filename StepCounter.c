#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array


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
    bool endProcess = false;
    char filename[100];
    while(!endProcess){
        printf("Menu Options\nA: Specify the filename to be imported\nB: Display the total number of records in the file\nC: Find the date and time of the timeslot with the fewest steps\nD: Find the date and time of the timeslot with the largest number of steps\nE: Find the mean step count of all the records in the file\nF: Find the longest continuous period where the step count is above 500 steps\nQ: Quit\n");

        char option;
        scanf (" %c", &option);


        switch (option) {
        case 'A':
            //Open the file in read mode.
            printf("Input filename: ");
            scanf("%s", filename);
            FILE *file = fopen(filename, "r");
            if (file == NULL) {
                printf("Error: Could not find or open the file.\n");
                return 1;
            }
            else{
                printf("File successfully loaded.\n");
            }
            break;
        case 'B':
            
            break;
        case 'C':
            //code
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
            return 0;
            break;
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    //Close the file.
    fclose(file);
    
    return 0;
}