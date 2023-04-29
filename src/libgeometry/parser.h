#pragma once

#define MAX_ELEMENTS 255
#define MIN_ELEMENTS 10
#define MAX_COORDS 4
#define FILE_ERROR 0
#define STRING_ERROR 0

typedef struct
{
    double x;
    double y;
    double radius;
} Coords;

typedef struct
{
    char name[MAX_ELEMENTS];
    char type[MIN_ELEMENTS];
    Coords coords[MAX_COORDS];
    int intersects[MIN_ELEMENTS];
} Figure;

int readFile(char *, Figure *, char *);
void printFigures(Figure *, int);
