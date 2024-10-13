#include <stdio.h>
#include <string.h>

// Constants
#define MAX_SECTIONS 100
#define MAX_BOOKS_PER_SECTION 100 // You can adjust this as needed
#define MAX_GENRE_LENGTH 50

// Book structure
typedef struct {
    char title[100];
    char author[100];
    int year;
    char genre[MAX_GENRE_LENGTH];
    int copiesAvailable;
    int borrowedCount; // To track borrowed transactions
} Book;

// Function prototypes
void readBookTransactionData(Book library[][MAX_BOOKS_PER_SECTION]);
void generateDailyTransactionReport(Book library[][MAX_BOOKS_PER_SECTION]);
void generateGenreSummary(Book library[][MAX_BOOKS_PER_SECTION]);

int main() {
    Book library[MAX_SECTIONS][MAX_BOOKS_PER_SECTION];

    // Initialize book data (you might want to read from a file in a real application)
    // ...

    readBookTransactionData(library);
    generateDailyTransactionReport(library);
    generateGenreSummary(library);

    return 0;
}

// Function to read book transaction data
void readBookTransactionData(Book library[][MAX_BOOKS_PER_SECTION]) {
    int sectionID, bookIndex, numTransactions;

    printf("Enter the number of book transactions: ");
    scanf("%d", &numTransactions);

    for (int i = 0; i < numTransactions; i++) {
        char transactionType[10]; // "borrow" or "return"

        printf("\nEnter details for transaction %d:\n", i + 1);
        printf("Section ID (1-100): ");
        scanf("%d", &sectionID);
        printf("Book Index within Section (1-100): ");
        scanf("%d", &bookIndex);
        printf("Transaction Type (borrow/return): ");
        scanf("%s", transactionType);

        sectionID--; // Adjust to 0-based indexing for array
        bookIndex--;

        if (strcmp(transactionType, "borrow") == 0) {
            if (library[sectionID][bookIndex].copiesAvailable > 0) {
                library[sectionID][bookIndex].copiesAvailable--;
                library[sectionID][bookIndex].borrowedCount++;
                printf("Book borrowed successfully.\n");
            } else {
                printf("Book not available for borrowing.\n");
            }
        } else if (strcmp(transactionType, "return") == 0) {
            library[sectionID][bookIndex].copiesAvailable++;
            printf("Book returned successfully.\n");
        } else {
            printf("Invalid transaction type.\n");
        }
    }
}

// Function to generate the daily transaction report
void generateDailyTransactionReport(Book library[][MAX_BOOKS_PER_SECTION]) {
    printf("\n\nDaily Transaction Report:\n");

    for (int i = 0; i < MAX_SECTIONS; i++) {
        for (int j = 0; j < MAX_BOOKS_PER_SECTION; j++) {
            if (library[i][j].borrowedCount > 0) {
                printf("Section %d, Book %d (%s): Borrowed %d times\n", 
                       i + 1, j + 1, library[i][j].title, library[i][j].borrowedCount);
            }
        }
    }
}

// Function to generate the summary of most borrowed genres
void generateGenreSummary(Book library[][MAX_BOOKS_PER_SECTION]) {
    int genreCount[MAX_SECTIONS] = {0}; // Assuming max genre count is same as sections
    char genreNames[MAX_SECTIONS][MAX_GENRE_LENGTH]; 
    int genreIndex = 0; 
    int totalTransactions = 0;

    for (int i = 0; i < MAX_SECTIONS; i++) {
        for (int j = 0; j < MAX_BOOKS_PER_SECTION; j++) {
            if (library[i][j].borrowedCount > 0) {
                totalTransactions += library[i][j].borrowedCount;

                // Find the genre in the list
                int found = 0;
                for (int k = 0; k < genreIndex; k++) {
                    if (strcmp(library[i][j].genre, genreNames[k]) == 0) {
                        genreCount[k] += library[i][j].borrowedCount;
                        found = 1;
                        break;
                    }
                }

                // If genre not found, add it to the list
                if (!found) {
                    strcpy(genreNames[genreIndex], library[i][j].genre);
                    genreCount[genreIndex] += library[i][j].borrowedCount;
                    genreIndex++;
                }
            }
        }
    }

    printf("\n\nSummary of Most Borrowed Genres:\n");
    printf("Total Transactions: %d\n", totalTransactions);

    // (Optional) You can add logic here to sort genres by borrowedCount 
    // to display the most borrowed ones first

    for (int i = 0; i < genreIndex; i++) {
        printf("Genre: %s, Borrowed Count: %d\n", genreNames[i], genreCount[i]);
    }
}