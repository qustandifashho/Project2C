#include <stdio.h>
#include <stdlib.h>
#include "route-records.h"

// should I remove and just use 1 and 0 for pt6???
#define TRUE 1
#define FALSE 0


int main( int argc, char *argv[] ){
    /* 1. Declare variables here */
    FILE* fileIn;
    RouteRecord* records;
    int numOfRecords;
    int menuChoice;

    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
    if (argc < 2) { // checks if there is fewer than 2 cmd prompt arguments if there is, filename argument is missing (can be 1)
        printf("ERROR: Missing file name\n"); // I am not sure if 2, but checking ./out and 1 argument here if there less then there is an error
        return 1; // meaning there is an error /////////I change argc to 1 and it worked? Not sure if right 
    }

    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */

    char* filename = argv[1];
    printf("\nOpening %s\n", filename);

    fileIn = NULL; // initialize file pointer fileIn to NULL
    fileIn = fopen(filename, "r"); // read

    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    if(fileIn == NULL){
        printf("ERROR: Could not open file\n");
        return 1;
    }

    /* 5. Do the following to load the records into an array of RouteRecords */
    //5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
    records = createRecords(fileIn);

    //5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    numOfRecords = fillRecords(records, fileIn);
    printf("Unique routes operated by airlines: %d\n", numOfRecords); ///////////////////////////////////////////////////////////////// SAYS 0



    // Print the data in the records array for verification
    for (int i = 0; i < numOfRecords; i++) {
        printf("Route %d: Origin: %s, Destination: %s, Airline: %s\n", i + 1, records[i].origin, records[i].destination, records[i].airline);
        for (int j = 0; j < 6; j++) {
            printf("  Month %d: %d\n", j + 1, records[i].passengerNum[j]);
        }
    }
   






    //5.3 Close the the file.
    fclose(fileIn);


    // 6. Create an infinite loop that will do the following:
    while(TRUE){
        // 6.1 Call printMenu()
        printMenu(); // printmenu() is void so no parameters


        // 6.2 Ask the user to input a value for the menu
        //printf("Enter your selection: "); // will be in voidmenu()
        while(scanf("%d", &menuChoice) != 1){ // gets the input from the user and checks if the return value of scanf is an int whihc is what we want. Not what the inout fromn us is, it is the return value. 
            printf("Please enter an integer from 1 to 5"); // do I need to clear the buffer? No. I do not . 
            while(getchar() != '\n');
        }

        // 6.4 Create a switch/case statement to handle all the menu options
        switch(menuChoice){
            case 1: {  // if menuChoice == 1 (Route)
                // Search by route 
                char origin[4];
                char destination[4];
                printf("Enter origin: "); 
                scanf("%3s", origin); // 3 char code
                printf("Enter destination: "); 
                scanf("%3s", destination); // 3 char code
                searchRecords(records, numOfRecords, origin, destination, ROUTE); // function searchRecords call
                break;
            }
            case 2: {  // if menuChoice == 2 (Origin Airport)
                printf("Enter Origin: ");
                scanf("%3s", records -> origin);
                searchRecords(records, numOfRecords, records->origin, NULL, ORIGIN);
                break;
            }
            case 3:{  // if menuChoice == 3 (Destination Airport)
                printf("Enter Destination: ");
                scanf("%3s", records -> destination);
                searchRecords(records, numOfRecords, NULL, records->destination, DESTINATION);
                break;
            }
            case 4: {  // if menuChoice == 4 (Airline)
                printf("\nEnter Airline: ");
                scanf("%2s", records -> airline);
                searchRecords(records, numOfRecords, NULL, NULL, AIRLINE);
                break;
            }
            case 5:  // if menuChoice == 5 (Quit)
                printf("Good-bye!");
                free(records);
                return 0;
        
            
            default: // else
                printf("Invalid choice.");
                break;

            }
        }

        return 0;
        
    }

    /* 1. Declare variables here */
    
    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: ERROR: Missing file name and end the program */
    
    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
    
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
    
    
    /* 5. Do the following to load the records into an array of RouteRecords
    	
    		5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.
    		
    		5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    		
    		5.3 Close the the file.
    */
    
    /* 6. Create an infinite loop that will do the following:
    
    		6.1 Call printMenu()
    		
    		6.2 Ask the user to input a value for the menu
    		
    		6.3 Handle the case in which a non-integer value is entered
    		
    		6.4 Create a switch/case statement to handle all the menu options
    		
	    		6.4.1 Each option requires the user to enter a search key
	    		
	    		6.4.2 Quit needs to free the array
            // I wrote this
            Column 1 = Month (1-12)
            Column 2 - origin airport
            Column 3 = Destination airport
            Column 4 = airline code (ex. AA = American Airlines)
            Column 5 = passenger category (?)
            Column 6 = total number of passengers in that month for that route
    
    */
