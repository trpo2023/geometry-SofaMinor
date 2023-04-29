#pragma once

#include <parser.h>
#include <stdbool.h>

int max(int, int);
int min(int, int);
int area(Coords, Coords, Coords);
bool boundingBox(int, int, int, int);
bool similarFigures(Figure, Figure);
bool differentFigures(Figure, Figure);
int getIntersections(Figure *, int, int);
void printIntersections(Figure *, int, int);
