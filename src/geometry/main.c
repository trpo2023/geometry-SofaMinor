#include <stdio.h>

#include <parser.h>

int main(int argc, char *argv[])
{
    if (argv[1] == NULL)
    {
        printf("The input is a file with format lines: 'circle(point, number)' "
               "or 'triangle((point, point, point, point))'\n");
        return 1;
    }

    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    int count = readFile(argv[1], figures, errmsg);
    printFigures(figures, count);

    return 0;
}
