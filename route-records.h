#ifndef ROUTE_RECORDS_H
#define ROUTE_RECORDS_H
#include <stdio.h>

// Create a struct named RouteRecord that will hold information about a route that is operated by one airline. 
// The struct will have the following data members:
// Origin code
// dest code
// Airline code
// Array of passenger count (0 = Jan)

typedef enum SearchType{ROUTE, ORIGIN, DESTINATION, AIRLINE} SearchType;

typedef struct{
    char origin[4]; // account for null char
    char destination[4];
    char airline[3];
    int passengerNum[6];
} RouteRecord;

// Write the functions used: 
RouteRecord* createRecords(FILE* fileIn);
int fillRecords(RouteRecord* r, FILE* fileIn);
int findAirlineRoute(RouteRecord* r, int length, const char* origin, const char* destination, const char* airline, int curIdx);
void searchRecords(RouteRecord* r, int length, const char* key1, const char* key2, SearchType st);
void printMenu();





#endif