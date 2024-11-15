#include "paintRoom.h"
#include <stdio.h> // Include this for printf if needed

void printName( )
{
    /* TODO : Fill in your name*/
    printf("\nThis solution was completed by:\n");
    printf("Alanna Matundan\n");
}

void paintRoom(RoomData room) {
    int i, j;
    int startRow = -1, startCol = -1; // Initialize to -1 to detect if 'A' is found

    // Find the position of 'A'
    for (i = 0; i < room.numrows; i++) {
        for (j = 0; j < room.numcols; j++) {
            if (room.roomArray[i][j] == 'A') {
                startRow = i;
                startCol = j;
                break; // Exit the inner loop when 'A' is found
            }
        }
        if (startRow != -1) break; // Exit the outer loop if 'A' was found
    }

    // Check if 'A' was found
    if (startRow == -1 || startCol == -1) {
        printf("Error: 'A' not found in room array.\n");
        return; // Exit if 'A' is not found
    }

    // Initialize the BFS queue
    int queue[room.numrows * room.numcols][2]; // To hold (row, col) pairs
    int front = 0, rear = 0; // Queue front and rear
    int visited[room.numrows][room.numcols]; // To track visited positions
    char stepCount[room.numrows][room.numcols]; // To store the step letters

    // Initialize the visited array and stepCount array
    for (i = 0; i < room.numrows; i++) {
        for (j = 0; j < room.numcols; j++) {
            visited[i][j] = 0; // Not visited
            stepCount[i][j] = room.roomArray[i][j]; // Copy original room
        }
    }

    // Start BFS from 'A'
    queue[rear][0] = startRow; // row
    queue[rear][1] = startCol; // col
    rear++;
    visited[startRow][startCol] = 1; // Mark 'A' as visited

    int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} }; // Right, Down, Left, Up
    int step = 1; // Initialize step count
    int currRow, currCol, size, k, d;

    while (front < rear) {
        size = rear - front; // Number of nodes at current step level

        for (k = 0; k < size; k++) {
            currRow = queue[front][0];
            currCol = queue[front][1];
            front++;

            for (d = 0; d < 4; d++) {
                int newRow = currRow + directions[d][0];
                int newCol = currCol + directions[d][1];

                // Check bounds and whether it is a valid move
                if (newRow >= 0 && newRow < room.numrows && newCol >= 0 && newCol < room.numcols &&
                    !visited[newRow][newCol] && room.roomArray[newRow][newCol] == ' ') {
                    visited[newRow][newCol] = 1; // Mark as visited
                    queue[rear][0] = newRow; // Enqueue the position
                    queue[rear][1] = newCol;
                    rear++;

                    // Determine the character to assign based on the number of steps
                    if (step <= 25) {
                        stepCount[newRow][newCol] = 'A' + step; // Set step character
                    } else {
                        stepCount[newRow][newCol] = 'Z'; // For 25+ steps
                    }
                }
            }
        }
        step++; // Increment step count after processing all nodes at the current level
    }

    // Copy back the step counts to the roomArray
    for (i = 0; i < room.numrows; i++) {
        for (j = 0; j < room.numcols; j++) {
            if (stepCount[i][j] != room.roomArray[i][j]) {
                room.roomArray[i][j] = stepCount[i][j]; // Update the room with the step count
            }
        }
    }
}
