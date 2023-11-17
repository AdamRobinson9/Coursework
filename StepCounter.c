#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here
// Global variables for filename and FITNESS_DATA array
FILE *file;
FITNESS_DATA *data;

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


//Method called when option C is chosen from menu to calculate the period with the fewest steps.
FITNESS_DATA optionC(){
    FITNESS_DATA fewestSteps;
    
    //loop through all items and check if step count is lower for that period than the current lowest count.
    for (int i = 0; i < noOfRecords(); i++){
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

//Method called when option D is chosen from the menu to calculate the period with the most steps.
FITNESS_DATA optionD(){
    FITNESS_DATA mostSteps;
    //loop through all items and check if step count is higher for that period than the current highest count.
    for (int i = 0; i < noOfRecords(); i++){
        if(i==0){
            mostSteps = data[i];
        }
        else{
            if(data[i].steps > mostSteps.steps){
                mostSteps = data[i];
            }
        }
    }
    return mostSteps;
}

//Method called when option E is chosen from the menu to calculate the mean no of steps.
int optionE(){
    int records = noOfRecords();
    int total = 0;
    //Step through all of the step counts and calculate a total.
    for(int i=0; i<records; i++){
        total = total + data[i].steps;
    }
    //Calculate the mean and return it.
    return total/records;
}

int optionF(){
    int highestCount = 0;
    int highestStart = 0;
    int start;
    for (int i=0; i<noOfRecords(); i++){
        if(data[i].steps > 500 && data[i-1].steps < 500){
            start = i;
            int currentCount = 0;
            while (data[i + currentCount].steps > 500){
                currentCount++;
            }
            if(currentCount > highestCount){
                highestCount = currentCount;
                highestStart = i;
            }
        }
    }
    printf("Longest period start: %s %s\n", data[highestStart].date, data[highestStart].time);
    printf("Longest period end: %s %s\n", data[highestStart + highestCount - 1].date, data[highestStart + highestCount - 1].time);
}

// Complete the main function
int main() {
    bool endProcess = false;
    char filename[100];
    while(!endProcess){
        //Print the menu of options.
        printf("Menu Options:\n"
                "A: Specify the filename to be imported\n"
                "B: Display the total number of records in the file\n"
                "C: Find the date and time of the timeslot with the fewest steps\n"
                "D: Find the date and time of the timeslot with the largest number of steps\n"
                "E: Find the mean step count of all the records in the file\n"
                "F: Find the longest continuous period where the step count is above 500 steps\n"
                "Q: Quit\n");

        //Read in the user's choice from the menu.
        char option;
        scanf (" %c", &option);

        //Process the user's choice.
        switch (option) {
        case 'A':
            //Open the file in read mode.
            printf("Input filename: ");
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
            break;
        case 'B':
            //Print the number of records in the file, counted by the noOfRecords method.
            printf("Total records: %d\n", noOfRecords());
            break;
        case 'C':
            //Print the date and time of the fewest steps period, calculated by the optionC method.
            printf("Fewest steps: %s %s\n", optionC().date, optionC().time);
            break;
        case 'D':
            //Print the date and time of the largest steps period, calculated by the optionD method.
            printf("Largest steps: %s %s\n", optionD().date, optionD().time);
            break;
        case 'E':
            //Print the mean steps from the data, calculated by the optionE method.
            printf("Mean step count: %d\n", optionE());
            break;
        case 'F':
            optionF();
            break;
        case 'Q':
            return 0;
            break;
        default:
            //Print an error messeage if an invalid option is chosen from menu.
            printf("Invalid choice. Try again.\n");
        }
    }    
    return 0;
}