#include <ctest.h>
#include <math.h>
#include <stdio.h>

#define _USE_MATH_DEFINES // M_PI in math.h

#include <calculations.h>
#include <intersections.h>
#include <lexer.h>
#include <parser.h>

// Проверяет сколько строк файла удалось прочитать
CTEST(INPUT_FILE, CHECK_AMOUNT_STRINGS)
{
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    errmsg[0] = '\0';
    ASSERT_EQUAL(3, readFile("data", figures, errmsg));
}

// Проверка на синтаксические ошибки в названии фигур
CTEST(SYNTAX_ERRORS, CHECK_STRING)
{
    FILE *file = fopen("test/input/ErrorsInWords.txt", "r");
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    char line[MAX_ELEMENTS];
    errmsg[0] = '\0';
    int count = 0;

    while (fgets(line, MAX_ELEMENTS, file))
    {
        ASSERT_EQUAL(1, stringHandler(line, &figures[count], errmsg));
        count++;
    }
    fclose(file);
}

// Проверка на ошибки в указании координат для фигур
CTEST(VALUES_ERRORS, CHECK_STRING)
{
    FILE *file = fopen("test/input/ErrorsInValues.txt", "r");
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    char line[MAX_ELEMENTS];
    errmsg[0] = '\0';
    int count = 0;

    while (fgets(line, MAX_ELEMENTS, file))
    {
        if (count < 2)
            ASSERT_EQUAL(1, triangleHandler(line, &figures[count], errmsg));
        else
            ASSERT_EQUAL(1, circleHandler(line, &figures[count], errmsg));
        count++;
    }
    fclose(file);
}

// Проверка функции, которая "вытаскивает" значение из строки и конвертирует его в double
CTEST(TAKE_ELEMENTS, TAKE_VALUE)
{
    FILE *file = fopen("data", "r");
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    char line[MAX_ELEMENTS];
    errmsg[0] = '\0';
    int count = 0;

    while (fgets(line, MAX_ELEMENTS, file))
    {
        if (count == 0)
        {
            int i = TRIANGLE_START + 2;
            ASSERT_DBL_NEAR(-3, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(-2, getValue(line, &i, &figures[count], ',', errmsg));
            i += 2;
            ASSERT_DBL_NEAR(-1, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(0, getValue(line, &i, &figures[count], ',', errmsg));
            i += 2;
            ASSERT_DBL_NEAR(-3, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(2, getValue(line, &i, &figures[count], ',', errmsg));
            i += 2;
            ASSERT_DBL_NEAR(-3, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(-2, getValue(line, &i, &figures[count], ')', errmsg));
        }
        else if (count == 1)
        {
            int i = CIRCLE_START + 1;
            ASSERT_DBL_NEAR(0, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(0, getValue(line, &i, &figures[count], ',', errmsg));
            i += 2;
            ASSERT_DBL_NEAR(1.5, getValue(line, &i, &figures[count], ')', errmsg));
        }
        else if (count == 2)
        {
            int i = TRIANGLE_START + 2;
            ASSERT_DBL_NEAR(3, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(-2, getValue(line, &i, &figures[count], ',', errmsg));
            i += 2;
            ASSERT_DBL_NEAR(3, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(2, getValue(line, &i, &figures[count], ',', errmsg));
            i += 2;
            ASSERT_DBL_NEAR(1, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(0, getValue(line, &i, &figures[count], ',', errmsg));
            i += 2;
            ASSERT_DBL_NEAR(3, getValue(line, &i, &figures[count], ' ', errmsg));
            i++;
            ASSERT_DBL_NEAR(-2, getValue(line, &i, &figures[count], ')', errmsg));
        }
        count++;
    }
    fclose(file);
}

// Проверяет правильно ли была найдена площадь окружности
CTEST(INPUT_FILE, CHECK_CIRCLE_AREA)
{
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    readFile("data", figures, errmsg);
    ASSERT_DBL_NEAR(M_PI * pow(figures[1].coords[0].radius, 2), circleArea(figures[1].coords));
}

// Проверка на правильное нахождение пересечений
CTEST(FIGURE_SET, CHECK_INTERSECTIONS)
{
    Figure figures[MIN_ELEMENTS];
    char errmsg[MAX_ELEMENTS];
    int count = readFile("data", figures, errmsg);
    int triangles[] = {2, 0};
    int circle[] = {1, 3, 0};
    for (int i = 0; i < count; i++)
    {
        getIntersections(figures, i, count);
        if (i == 1)
        {
            for (int j = 0; j < count; j++)
            {
                ASSERT_EQUAL(circle[j], figures[i].intersects[j]);
            }
        }
        else
        {
            for (int j = 0; j < count - 1; j++)
            {
                ASSERT_EQUAL(triangles[j], figures[i].intersects[j]);
            }
        }
    }
}
