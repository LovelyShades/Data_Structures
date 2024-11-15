#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct RoomData
{
    char **roomArray; /* the 2d char array representing the room */
    int numrows;      /* the number of rows for the char** roomArray */
    int numcols;      /* the number of columns for the char** roomArray */
} RoomData;

RoomData read2DArray(const char *name);
void print2DArray(RoomData room);
void free2DArray(RoomData room);
void recFill(RoomData room, int row, int col);

/* change the following constants to add/remove some cases for testing */
const int numFiles = 2;
const int numTests = 3;
const char *defaultFilenames[] = {"room-Default01.txt", "room-NewTests01.txt"};
const int defaultRow[] = {3, 3, 0};
const int defaultCol[] = {4, 1, 0};

/************************** DO NOT MODIFY THESE FUNCTIONS BELOW **************************/

int main(int argc, char *argv[])
{
    int i, j;
    RoomData room;
    printf("Running default test files: \n\n");

    for (i = 0; i < numFiles; i++)
    {
        for (j = 0; j < numTests; j++)
        {
            printf("\n--------------- START OF OUTPUT FOR %s, %d, %d -----------------\n\n", defaultFilenames[i], defaultRow[j], defaultCol[j]);
            room = read2DArray(defaultFilenames[i]);
            printf("Base room: \n\n");
            print2DArray(room);
            recFill(room, defaultRow[j], defaultCol[j]);
            printf("\nRoom after algorithm: \n\n");
            print2DArray(room);
            free2DArray(room);
            printf("\n--------------- END OF OUTPUT FOR %s -----------------\n\n", defaultFilenames[i]);
        }
    }
    return 0;
}

/* Read in and return room from given file*/
RoomData read2DArray(const char *name)
{
    int i, j;
    FILE *f = fopen(name, "r");
    char buffer[100];
    char *line;
    RoomData room;

    if (f == NULL || fgets(buffer, 100, f) == NULL || sscanf(buffer, "%d%d", &room.numrows, &room.numcols) != 2)
    {
        printf("ERROR - Invalid file format %s\n", name);
        exit(-1);
    }

    line = (char *)malloc(sizeof(char) * (room.numcols + 10));
    room.roomArray = (char **)malloc(sizeof(char *) * (room.numrows));

    for (i = 0; i < room.numrows; i++)
    {
        room.roomArray[i] = (char *)malloc(sizeof(char) * (room.numcols));
        if (fgets(line, room.numcols + 10, f) == NULL)
        {
            printf("ERROR - Failed to read %dth row\n", i + 1);
            exit(-1);
        }
        for (j = 0; j < room.numcols; j++)
            room.roomArray[i][j] = line[j];
    }
    free(line);
    fclose(f);
    return room;
}

/*Print 2D array */
void print2DArray(RoomData room)
{
    int i, j;
    for (i = 0; i < room.numrows; i++)
    {
        for (j = 0; j < room.numcols; j++)
            printf("%c", room.roomArray[i][j]);
        printf("\n");
    }
}

/* Free given 2D array */
void free2DArray(RoomData room)
{
    int i;
    for (i = 0; i < room.numrows; i++)
        free(room.roomArray[i]);
    free(room.roomArray);
}

/************************** DO NOT MODIFY ABOVE FUNCTIONS **************************/

/* Recursive fill function */
void recFill(RoomData room, int row, int col)
{
    /* Base case 1: */
    if (row < 0 || row >= room.numrows || col < 0 || col >= room.numcols)
    {
        return;
    }

    /* Base case 2: */
    if (room.roomArray[row][col] == '*' || room.roomArray[row][col] == '#')
    {
        return;
    }

    /* Fill the current space */
    room.roomArray[row][col] = '#';

    /* Recursive calls to explore all directions */
    recFill(room, row - 1, col); /* Move up*/
    recFill(room, row + 1, col); /* Move down*/
    recFill(room, row, col - 1); /* Move left*/
    recFill(room, row, col + 1); /* Move right*/
}
