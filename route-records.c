#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"

RouteRecord* createRecords( FILE* fileIn ){
    int countRecords = 0; // initialize to count number of records in the csv file
    char buffer[256]; // large enough to read csv file

    // Counting and updating the number of records in the file with a while loop. 
    while (fgets(buffer, sizeof(buffer), fileIn) != NULL) {
        countRecords++;
    }

    // Dynamically allocate memory for an array of RouteRecord’s based on the count.
    RouteRecord* records = (RouteRecord*)malloc(countRecords * sizeof(RouteRecord));

    // Each RouteRecord struct object has an array of 6 integers to hold the number of passengers for 
    // six months. Initialize each of these integer values to 0. 
    // You do not need to initialize the other data members in the struct
    int i;
    int j;
    for(i = 0; i < countRecords; i++){
        for(j = 0; j < 6; j++){
            records[i].passengerNum[j] = 0;
        }
    }

    // Rewind the file pointer not really sure if this is right 
    rewind(fileIn);

    // Return the pointer to the array you dynamically allocated.
    return records;


}

// This function will process the data in the CSV file. 
// Essentially, the code will go through each record, parse out the record, and enter it into the array. 
int fillRecords( RouteRecord* r, FILE* fileIn ){


// The function will call findAirlineRoute() to see if the exact route with the origin, destination, and airline was already entered in the array. 
// If it was found, then you will update the existing record in your array with the passenger data for that month. 
// Recall there should be six entries (one for each month) for each route operated by an airline. 
// If the route operated by the airline does not already exist in the array, add this new route to the array
    int countRecords = 0;

    // Read each line in CSV
    // %*d = discards month (dont need rn)
    // The rest are for the specific data in each column of the csv fikle. 
    while (fscanf(fileIn, "%*d,%3s,%3s,%2s,%*s,%d,%d,%d,%d,%d,%d", r[countRecords].origin, r[countRecords].destination, r[countRecords].airline, &r[countRecords].passengerNum[0], &r[countRecords].passengerNum[1], &r[countRecords].passengerNum[2], &r[countRecords].passengerNum[3], &r[countRecords].passengerNum[4], &r[countRecords].passengerNum[5]) == 9) { // works if gets 9 items from the data (stats)
            // Call findAirlineRoute to see if the route already exists in the array
            int exists = findAirlineRoute(r, countRecords, r[countRecords].origin, r[countRecords].destination, r[countRecords].airline, countRecords);

            if (exists == -1) {
            // The route does not exist in the array, add this new route
            countRecords++; // Increment the counter for the number of RouteRecords used in the array
        } else {
            // The route already exists in the array, update the existing record with passenger data for that month (months Jan - June or 1-6 (idices 0-5))
            r[exists].passengerNum[0] += r[countRecords].passengerNum[0];
            r[exists].passengerNum[1] += r[countRecords].passengerNum[1];
            r[exists].passengerNum[2] += r[countRecords].passengerNum[2];
            r[exists].passengerNum[3] += r[countRecords].passengerNum[3];
            r[exists].passengerNum[4] += r[countRecords].passengerNum[4];
            r[exists].passengerNum[5] += r[countRecords].passengerNum[5];
        }
    }
    return countRecords; // Return the actual number of RouteRecords used in the array
}


    // seeing if they match
    int findAirlineRoute( RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx ){
        // Base case: If we have reached the end of the array, return -1 (route not found)
        if (curIdx >= length) {
            return -1; // cannot find these three strings in the same struct object
    }
    // if the strings are equal it return 0
    if (strcmp(r[curIdx].origin, origin) == 0 && strcmp(r[curIdx].destination, destination) == 0 && strcmp(r[curIdx].airline, airline) == 0) {
        return curIdx; // Return the index of the matched route
    }
    // Recursive  Continue searching in the next record
    // recursive because this function calls itself
    return findAirlineRoute(r, length, origin, destination, airline, curIdx + 1); // adding 1 to current index. , the function moves on to the next element in the array to check if it matches the specified origin, destination, and airline codes.
    // keeps calling until a match is found 
}

// This function searches the RouteRecord array and prints out the results of the search
void searchRecords( RouteRecord* r, int length, const char* key1, const char* key2, SearchType st ) {
    int matchesNum = 0; // number of matches 
    int numOfPassengers = 0; // number of passengers tot
    int numOfPassengersByMonth[6] = {0}; // 6 months 

    // Printing based on user Input
    printf("Searching by ");
    if(st == ROUTE){
        printf("route...\n");
    }
    else if(st == ORIGIN){
        printf("origin...\n");
    }
    else if(st == DESTINATION){
        printf("destination...\n");
    }
    else{
        printf("airline...");
    }

    // For ORIGIN, DESTINATION, AIRLINE, key1 will hold the value you are looking for. 
    // For ROUTE, you are searching both the origin and destination and airport, so key1 and key2 will hold those values, 
    // respectively, that you will use to compare against the data members. 
    // For example, if the search is by the destination: st will be equal to DESTINATION, key1 will have an airport code that the user entered,
    //  and you will compare each struct’s destination data member against the airport code.
    // use for loop to iterate
    int match = 0;
    for(int i = 0; i < length; i++){
        //Compare both origin and destination with key1 and key2 for ROUTE search
        if(st == ROUTE){
            match = strcmp(r[i].origin, key1) == 0 && strcmp(r[i].destination, key2) == 0;
        }
        // Compare origin with key1 for ORIGIN search
        else if(st == ORIGIN){
            match = strcmp(r[i].origin, key1) == 0;
        }
        // Compare destination with key1 for DESTINATION search
        else if(st == DESTINATION){
            match = strcmp(r[i].destination, key1) == 0;
        }
        // Compare airline with key1 for AIRLINE search
        else if(st == AIRLINE){
            match = strcmp(r[i].airline, key1) == 0;

        }

        if (match) {
            printf("%s (%s-%s) ", r[i].airline, r[i].origin, r[i].destination);
            numOfPassengers += r[i].passengerNum[0] + r[i].passengerNum[1] + r[i].passengerNum[2] + r[i].passengerNum[3] + r[i].passengerNum[4] + r[i].passengerNum[5];
            for (int j = 0; j < 6; j++) {
                numOfPassengersByMonth[j] += r[i].passengerNum[j];
            }
            matchesNum++;
        }
    }

    // Note that you must handle any instances where you the search has 0 results.
    if(matchesNum == 0){
        printf("0 matches were found\n");
        return; // So i can terminate the program here and not go to the next print statements 
    }
    // Stats printing 
    printf("\n\nStatistics\n");
    printf("Total Passengers:                 %d\n", numOfPassengers);
    printf("Total Passengers in Month 1:      %d\n", numOfPassengersByMonth[0]);
    printf("Total Passengers in Month 2:      %d\n", numOfPassengersByMonth[1]);
    printf("Total Passengers in Month 3:      %d\n", numOfPassengersByMonth[2]);
    printf("Total Passengers in Month 4:      %d\n", numOfPassengersByMonth[3]);
    printf("Total Passengers in Month 5:      %d\n", numOfPassengersByMonth[4]);
    printf("Total Passengers in Month 6:      %d\n", numOfPassengersByMonth[5]);
    printf("\nAverage Passengers per Month:     %d\n\n", numOfPassengers / matchesNum);
}


void printMenu() {
    printf("\n\n######### Airline Route Records Database MENU #########\n");
    printf("1. Search by Route\n");
    printf("2. Search by Origin Airport\n");
    printf("3. Search by Destination Airport\n");
    printf("4. Search by Airline\n");
    printf("5. Quit\n");
    printf("Enter your selection: ");
}

