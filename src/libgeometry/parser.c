#include <stdio.h>
#include <string.h>

#include <calculations.h>
#include <intersections.h>
#include <lexer.h>
#include <parser.h>

int readFile(char *fileName, Figure *figures, char *errmsg)
{
    FILE *file = fopen(fileName, "r");
    if (file == NULL)
    {
        printf("Error! Failed to open file!\n");
        fclose(file);
        return FILE_ERROR;
    }

    errmsg[0] = '\0';
    int count = 0;
    char line[MAX_ELEMENTS];

    while (fgets(line, MAX_ELEMENTS, file))
    {
        if (line[strlen(line) - 1] != '\n') // Для последней строки
        {
            int length = strlen(line);
            line[length] = '\n';
            line[length + 1] = '\0';
        }
        stringHandler(line, &figures[count], errmsg);
        if (strlen(errmsg))
        {
            char temp[MIN_ELEMENTS];
            sprintf(temp, "%d", count + 1);
            printf("%d. %s", count + 1, line);
            addSpaces(strlen(temp) + 2);
            printf("%s\n", errmsg);
            return STRING_ERROR;
        }
        count++;
    }
    fclose(file);
    return count;
}

void printFigures(Figure *figures, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d. %s\n", i + 1, figures[i].name);
        if (!strcmp(figures[i].type, "circle"))
        {
            printf("\tperimeter = %.3lf\n", circlePerimeter(figures[i].coords));
            printf("\tarea = %.3lf\n", circleArea(figures[i].coords));
            printf("\tintersects:\n");
            printIntersections(figures, i, n);
        }
        else if (!strcmp(figures[i].type, "triangle"))
        {
            double perimeter = trianglePerimeter(figures[i].coords);
            printf("\tperimeter = %.3lf\n", perimeter);
            printf("\tarea = %.3lf\n", triangleArea(figures[i].coords, perimeter / 2));
            printf("\tintersects:\n");
            printIntersections(figures, i, n);
        }
        printf("\n");
    }
}
