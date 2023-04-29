#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <parser.h>

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if (a < b)
        return a;
    return b;
}

int area(Coords a, Coords b, Coords c)
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

bool boundingBox(int a, int b, int c, int d)
{
    if (a > b)
    {
        int temp = a;
        a = b;
        b = temp;
    }
    if (c > d)
    {
        int temp = c;
        c = d;
        d = temp;
    }
    return max(a, c) <= min(b, d);
}

bool similarFigures(Figure current, Figure figure)
{
    Coords *f_coords = current.coords;
    Coords *s_coords = figure.coords;
    if (!strcmp(current.type, "circle"))
    {
        double length =
            sqrt(pow(abs((f_coords[0].x - s_coords[0].x)), 2) + pow(abs((f_coords[0].y - s_coords[0].y)), 2));
        double r_sum = f_coords[0].radius + s_coords[0].radius;
        return length < r_sum;
    }
    else if (!strcmp(current.type, "triangle"))
    {
        for (int i = 0; i < MAX_COORDS - 1; i++)
        {
            Coords a = current.coords[i];
            Coords b = current.coords[i + 1];
            for (int j = 0; j < MAX_COORDS - 1; j++)
            {
                Coords c = figure.coords[j];
                Coords d = figure.coords[j + 1];
                if (boundingBox(a.x, b.x, c.x, d.x) && boundingBox(a.y, b.y, c.y, d.y) &&
                    (area(a, b, c) * area(a, b, d) <= 0) && (area(c, d, a) * area(c, d, b) <= 0))
                    return true;
            }
        }
    }
    return false;
}

bool differentFigures(Figure current, Figure figure)
{
    Coords *circleCoords, *triangleCoords;
    if (!strcmp(current.type, "circle"))
    {
        circleCoords = current.coords;
        triangleCoords = figure.coords;
    }
    else if (!strcmp(current.type, "triangle"))
    {
        circleCoords = figure.coords;
        triangleCoords = current.coords;
    }

    for (int i = 0; i < MAX_COORDS - 1; i++)
    {
        double x1 = triangleCoords[i].x;
        double x2 = triangleCoords[i + 1].x;
        double xc = circleCoords[0].x;
        double y1 = triangleCoords[i].y;
        double y2 = triangleCoords[i + 1].y;
        double yc = circleCoords[0].y;
        double R = circleCoords[0].radius;

        double a = pow((x2 - x1), 2) + pow((y2 - y1), 2);
        double b = 2 * x1 * (x2 - x1) - 2 * (x2 - x1) * xc + 2 * y1 * (y2 - y1) - 2 * (y2 - y1) * yc;
        double c = pow(x1, 2) + pow(xc, 2) - 2 * x1 * xc + pow(y1, 2) + pow(yc, 2) - 2 * y1 * yc - pow(R, 2);

        double D = pow(b, 2) - 4 * a * c;

        double t1 = ((-1 * b) + sqrt(D)) / (2 * a);
        double t2 = ((-1 * b) - sqrt(D)) / (2 * a);

        if (((t1 >= 0) && (t1 <= 1)) || ((t2 >= 0) && (t2 <= 1)))
            return true;
    }
    return false;
}

int getIntersections(Figure *figures, int current, int total)
{
    char *currentType = figures[current].type;
    int j = 0;

    for (int i = 0; i < total; i++)
    {
        if (i != current)
        {
            char *figureType = figures[i].type;
            if (!strcmp(currentType, figureType))
            {
                if (similarFigures(figures[current], figures[i]))
                {
                    figures[current].intersects[j] = i + 1;
                    j++;
                }
            }
            else
            {
                if (differentFigures(figures[current], figures[i]))
                {
                    figures[current].intersects[j] = i + 1;
                    j++;
                }
            }
        }
    }
    figures[current].intersects[j] = 0;
    return j;
}

void printIntersections(Figure *figures, int current, int total)
{
    int el = 0;
    if (getIntersections(figures, current, total))
    {
        while (figures[current].intersects[el])
        {
            printf("\t  %d. %s\n", figures[current].intersects[el], figures[figures[current].intersects[el] - 1].type);
            el++;
        }
    }
    else
    {
        printf("\t  None\n");
    }
}
