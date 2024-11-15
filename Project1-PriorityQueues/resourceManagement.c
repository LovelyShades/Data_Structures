#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "resourceManagement.h"
#include "department.h"
#include "queue.h"

#define MAX_ITEMS 500
#define STRING_LENGTH 31

typedef struct {
    char departmentName[50];
    char itemName[50];
    double price;
} PurchasedItem;

typedef struct {
    char itemName[50];
    double price;
} ReceivedItem;

typedef struct {
    char itemName[50];
    double price;
} NotReceivedItem;

// Arrays to hold the items
PurchasedItem purchasedItems[MAX_ITEMS]; // Adjust MAX_ITEMS as needed
ReceivedItem receivedItems[MAX_ITEMS];
NotReceivedItem notReceivedItems[MAX_ITEMS];
int numPurchasedItems = 0; // Global variable to keep track of purchased items

// Function Prototypes
double minDouble(double x, double y);
Department* readDepartment(char *fileName);
void distributeBudget(double budget, PriorityQueue *deptPQ);
void freeDepartment(Department *dept);
void printResults(Department* departments[], int testDataSize, double totalBudget);
void printNames(void);
void sortDepartmentsBySpent(Department* departments[], int testDataSize);

// Prints the names of the authors
void printNames() {
    printf("\nThis solution was completed by:\n");
    printf("Alanna Matundan\n");
    printf("N/A\")>\n\n");
}

// Main function for resource management
void ResourceManagement(char* fileNames[], int testDataSize, double budget) {
    int i; 
    Department **departments = malloc(sizeof(Department*) * testDataSize);
    
    // Reset purchased items count for each test case
    numPurchasedItems = 0;

    // Read departments from files
    for (i = 0; i < testDataSize; i++) {
        departments[i] = readDepartment(fileNames[i]);
    }

    PriorityQueue *deptPQ = createPQ();

    // Enqueue departments by priority
    for (i = 0; i < testDataSize; i++) {
        enqueueByPriority(deptPQ, departments[i], 0.0);
    }

    // Distribute the budget among the departments
    distributeBudget(budget, deptPQ);

    // Sort departments by total spent before printing results
    sortDepartmentsBySpent(departments, testDataSize);
    printResults(departments, testDataSize, budget);

    // Free memory
    for (i = 0; i < testDataSize; i++) {
        free(departments[i]->name);
        freeQueue(departments[i]->itemsDesired);
        freeQueue(departments[i]->itemsReceived);
        freeQueue(departments[i]->itemsRemoved);
        free(departments[i]);
    }
    free(departments);
}

// Function to get the minimum of two doubles
double minDouble(double x, double y) {
    return (x <= y) ? x : y;
}

// Read a department from a file
Department* readDepartment(char *fileName) {
    FILE *f = fopen(fileName, "r");
    if (f == NULL) {
        printf("ERROR - Invalid file %s\n", fileName);
        exit(-1);
    }

    Department *dept = malloc(sizeof(Department));
    dept->name = malloc(STRING_LENGTH * sizeof(char));
    dept->itemsDesired = createQueue();
    dept->itemsReceived = createQueue();
    dept->itemsRemoved = createQueue();
    dept->totalSpent = 0.0;

    fscanf(f, "%s", dept->name);

    char itemName[STRING_LENGTH];
    double itemPrice;
    while (fscanf(f, "%s", itemName) == 1) {
        fscanf(f, "%lf", &itemPrice);
        Item *item = malloc(sizeof(Item));
        item->name = strdup(itemName);
        item->price = itemPrice;
        enqueue(dept->itemsDesired, item);
    }

    fclose(f);
    return dept;
}

void distributeBudget(double budget, PriorityQueue *deptPQ) {
    Department *currentDept;
    Item *desiredItem;
    int allDepartmentsEmpty; // Flag to check if all departments have no items
    int departmentsProcessed; // Count how many departments were processed
    int i;
    
    

    // Continue processing until budget is 0 and all departments are empty
    while (1) {
        allDepartmentsEmpty = 1; // Assume all are empty until proven otherwise
        departmentsProcessed = 0; // Reset for each round

        // Loop through the departments in the queue
        for (i = 0; i < sizeOfPriorityQueue(deptPQ); i++) {
            currentDept = dequeuePQ(deptPQ); // Get the current department

            // Check if there are still desired items
            if (!isEmpty(currentDept->itemsDesired)) {
                allDepartmentsEmpty = 0; // At least one department has items
                departmentsProcessed++; // Increment processed departments

                // Get the next desired item
                desiredItem = getNext(currentDept->itemsDesired);

                // Check if the desired item is affordable
                if (desiredItem->price <= budget) {
                    // Add to items received and deduct from budget
                    enqueue(currentDept->itemsReceived, dequeue(currentDept->itemsDesired));
                    currentDept->totalSpent += desiredItem->price;
                    budget -= desiredItem->price; // Deduct from budget

                    // Record the purchased item
                    strcpy(purchasedItems[numPurchasedItems].departmentName, currentDept->name);
                    strcpy(purchasedItems[numPurchasedItems].itemName, desiredItem->name);
                    purchasedItems[numPurchasedItems].price = desiredItem->price;
                    numPurchasedItems++;
                } else {
                    // Move item to not received
                    enqueue(currentDept->itemsRemoved, dequeue(currentDept->itemsDesired));
                }
            } 
            
            // If the department has no more items, grant a scholarship
            if (isEmpty(currentDept->itemsDesired)) {
                double scholarship = (budget >= 1000) ? 1000 : budget;
                
                if (scholarship > 0) {
                    currentDept->totalSpent += scholarship;
                    budget -= scholarship;

                    // Create a new scholarship item
                    Item *scholarshipItem = malloc(sizeof(Item));
                    scholarshipItem->name = strdup("Scholarship");
                    scholarshipItem->price = scholarship;
                    enqueue(currentDept->itemsReceived, scholarshipItem);

                    // Record the scholarship purchase
                    strcpy(purchasedItems[numPurchasedItems].departmentName, currentDept->name);
                    strcpy(purchasedItems[numPurchasedItems].itemName, "Scholarship");
                    purchasedItems[numPurchasedItems].price = scholarship;
                    numPurchasedItems++;
                }
            }

            enqueueByPriority(deptPQ, currentDept, currentDept->totalSpent);
        }

        // Exit loop if the budget is 0 and all departments have no items left
        if (budget <= 0 && allDepartmentsEmpty) {
            break;
        }
    }
}


// Sort departments by total spent
void sortDepartmentsBySpent(Department* departments[], int testDataSize) {
    int i, j;
    for (i = 0; i < testDataSize - 1; i++) {
        for (j = i + 1; j < testDataSize; j++) {
            if (departments[i]->totalSpent > departments[j]->totalSpent) {  // Sort by total spent in descending order
                // Swap departments
                Department* temp = departments[i];
                departments[i] = departments[j];
                departments[j] = temp;
            }
        }
    }
}

// Print results of department spending
void printResults(Department* departments[], int testDataSize, double totalBudget) {
    char priceString[20];
    int i;

    // Print purchased items first
    printf("ITEMS PURCHASED\n");
    printf("----------------------------\n");
    for (i = 0; i < numPurchasedItems; i++) {
        // Set a price string with two decimal places
        sprintf(priceString, "$%.2lf", purchasedItems[i].price);
        
        // Print the item with the department name for each item
        printf("Department of %-30s - %-30s - %20s\n", purchasedItems[i].departmentName, purchasedItems[i].itemName, priceString);
    }
    
    // Now print department summaries
    for (i = 0; i < testDataSize; i++) {
        Department *dept = departments[i];

        // Print department name, total spent, and percent of budget
        printf("\nDepartment of %s\n", dept->name);
        printf("Total Spent       = $%.2f\n", dept->totalSpent);
        printf("Percent of Budget = %.2f%%\n", (dept->totalSpent / totalBudget) * 100);
        printf("----------------------------\n");

        // Print items received
        printf("ITEMS RECEIVED\n");
        if (isEmpty(dept->itemsReceived)) {
            printf("\n");
        } else {
            LLNode *current = dept->itemsReceived->qFront;
            double totalReceived = 0.0; // Track total of items received
            while (current != NULL) {
                sprintf(priceString, "$%.2lf", current->qt->price);
                printf("%-30s - %20s\n", current->qt->name, priceString);
                totalReceived += current->qt->price; // Accumulate the total received
                current = current->pNext;
            }
        }

        // Print items not received
        printf("\nITEMS NOT RECEIVED\n");
        if (isEmpty(dept->itemsRemoved)) {
            printf("\n");
        } else {
            LLNode *current = dept->itemsRemoved->qFront;
            while (current != NULL) {
                sprintf(priceString, "$%.2lf", current->qt->price);
                printf("%-30s - %20s\n", current->qt->name, priceString);
                current = current->pNext;
            }
        }
    }
}



