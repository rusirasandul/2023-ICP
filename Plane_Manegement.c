#include <stdio.h>
#include <string.h>

// Constants
#define MAX_ROWS 50
#define MAX_SEAT_LETTERS 6   // A, B, C, D, E, F
#define MAX_CLASSES 3       // 0: Economy, 1: Business, 2: First

// Seat structure
typedef struct {
    char passengerName[50];
    int row;
    char seatLetter;
    int status;             // 0: Available, 1: Reserved
    int class;              // 0: Economy, 1: Business, 2: First
} Seat;

// Function prototypes
void readSeatReservationData(Seat airplane[][MAX_SEAT_LETTERS]);
void printDailySeatReservationReport(Seat airplane[][MAX_SEAT_LETTERS]);
void printSummarySeatAvailabilityReport(Seat airplane[][MAX_SEAT_LETTERS]);

int main() {
    Seat airplane[MAX_ROWS][MAX_SEAT_LETTERS]; 

    // Initialize all seats as available
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_SEAT_LETTERS; j++) {
            airplane[i][j].status = 0; // 0 means available
            strcpy(airplane[i][j].passengerName, ""); 
        }
    }

    readSeatReservationData(airplane);
    printDailySeatReservationReport(airplane);
    printSummarySeatAvailabilityReport(airplane);

    return 0;
}

// Function to read seat reservation data
void readSeatReservationData(Seat airplane[][MAX_SEAT_LETTERS]) {
    int numReservations;
    printf("Enter the number of seat reservations: ");
    scanf("%d", &numReservations);

    for (int i = 0; i < numReservations; i++) {
        char seat[5]; // e.g., "12A"
        int row, class;

        printf("\nEnter details for reservation %d:\n", i + 1);
        printf("Passenger Name: ");
        scanf(" %[^\n]", airplane[i][0].passengerName); 
        printf("Seat Number (e.g., 12A): ");
        scanf("%s", seat);
        printf("Class (0: Economy, 1: Business, 2: First): ");
        scanf("%d", &class);

        // Extract row number from seat string (e.g., "12" from "12A")
        row = (seat[0] - '0') * 10 + (seat[1] - '0'); 

        // Calculate array indices and store data
        airplane[row - 1][seat[2] - 'A'].row = row;
        airplane[row - 1][seat[2] - 'A'].seatLetter = seat[2];
        airplane[row - 1][seat[2] - 'A'].status = 1; // 1 means reserved
        airplane[row - 1][seat[2] - 'A'].class = class;
    }
}

// Function to print the daily seat reservation report
void printDailySeatReservationReport(Seat airplane[][MAX_SEAT_LETTERS]) {
    printf("\n\nDaily Seat Reservation Report:\n");

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_SEAT_LETTERS; j++) {
            if (airplane[i][j].status == 1) {
                printf("Seat %d%c: %s (%s Class)\n", 
                       airplane[i][j].row, 
                       airplane[i][j].seatLetter, 
                       airplane[i][j].passengerName,
                       (airplane[i][j].class == 0) ? "Economy" : 
                       (airplane[i][j].class == 1) ? "Business" : "First");
            }
        }
    }
}

// Function to print the summary seat availability report
void printSummarySeatAvailabilityReport(Seat airplane[][MAX_SEAT_LETTERS]) {
    int reserved = 0, available = 0;
    int classCount[MAX_CLASSES] = {0}; // To count seats per class

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_SEAT_LETTERS; j++) {
            if (airplane[i][j].status == 1) {
                reserved++;
                classCount[airplane[i][j].class]++; 
            } else {
                available++;
            }
        }
    }

    printf("\n\nSummary Seat Availability Report:\n");
    printf("Total Reserved Seats: %d\n", reserved);
    printf("Total Available Seats: %d\n", available);
    printf("Economy Class Reservations: %d\n", classCount[0]);
    printf("Business Class Reservations: %d\n", classCount[1]);
    printf("First Class Reservations: %d\n", classCount[2]);
}