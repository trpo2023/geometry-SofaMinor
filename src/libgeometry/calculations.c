#include <math.h>

#include <parser.h>

double circlePerimeter(Coords *coords)
{
    return 2 * M_PI * coords[0].radius;
}

double trianglePerimeter(Coords *coords)
{
    if ((coords[0].x != coords[MAX_COORDS - 1].x) || (coords[0].y != coords[MAX_COORDS - 1].y))
    {
        return -1;
    }

    double sum = 0;
    for (int i = 1; i < MAX_COORDS; i++)
    {
        sum += sqrt(pow((coords[i].x - coords[i - 1].x), 2) + pow((coords[i].y - coords[i - 1].y), 2));
    }

    return sum;
}

double circleArea(Coords *coords)
{
    return M_PI * (coords[0].radius * coords[0].radius);
}

double triangleArea(Coords *coords, double halfPerimeter)
{
    if ((coords[0].x != coords[MAX_COORDS - 1].x) || (coords[0].y != coords[MAX_COORDS - 1].y))
    {
        return -1;
    }

    double prod = halfPerimeter;
    for (int i = 1; i < MAX_COORDS; i++)
    {
        prod *= halfPerimeter - sqrt(pow((coords[i].x - coords[i - 1].x), 2) + pow((coords[i].y - coords[i - 1].y), 2));
    }

    return sqrt(prod);
}
