#include <stdio.h>
#include <string.h>
#include <ctype.h>

int check_num(char figure[], int *p)
{
    int k = *p;

    char str2[13] = "-.0123456789";

    while (figure[k] == ' ')
    {
        k++;
    }

    if (figure[k] == '0')
    {
        if (figure[k + 1] != '.' && strchr(str2, figure[k + 1]) != NULL)
        {
            printf("Error at column %d: expected '.' \n", k);
            return 0;
        }
    }

    if (strchr(str2, figure[k]) == NULL)
    {
        printf("Error at column %d: unexpected character\n", k);
        return 0;
    }

    while (strchr(str2, figure[k]) != NULL)
    {
        k++;
    }

    if (figure[k] == ',' || figure[k] == ')')
    {
        printf("Error at column %d: expected number\n", k);
        return 0;
    }

    if (figure[k] != ' ')
    {
        printf("Error at column %d: expected ' '\n", k);
        return 0;
    }

    while (figure[k] == ' ')
    {
        k++;
    }

    if (figure[k] == '0')
    {
        if (figure[k + 1] != '.' && strchr(str2, figure[k + 1]) != NULL)
        {
            printf("Error at column %d: expected '.'\n", k);
            return 0;
        }
    }

    if (strchr(str2, figure[k]) == NULL)
    {
        printf("Error at column %d: unexpected character\n", k);
        return 0;
    }

    while (strchr(str2, figure[k]) != NULL)
    {
        k++;
    }

    while (figure[k] == ' ')
    {
        k++;
    }

    k++;
    *p = k;
    return 1;
}

void circle(char figure[])
{
    char str[6] = "circle";
    char str2[13] = "-.0123456789";

    for (int i = 0; i < 5; i++)
    {
        figure[i] = tolower(figure[i]);
        if (figure[i] != str[i])
        {
            char strerr[6];
            strncpy(strerr, figure, 6);
            strerr[6] = '\0';
            printf("Error at column 0: expected 'circle' instead of %s\n", strerr);
            return;
        }
    }

    int k = 7;

    if (figure[6] != '(')
    {
        printf("Error at column %d: expected '('\n", k);
        return;
    }

    if (check_num(figure, &k) == 0)
    {
        return;
    }

    if (figure[k - 1] != ',')
    {
        printf("Error at column %d: expected ','\n", k);
    }

    while (figure[k] == ' ')
    {
        k++;
    }

    if (figure[k] == '0')
    {
        if (figure[k + 1] != '.' && strchr(str2, figure[k + 1]) != NULL)
        {
            printf("Error at column %d: expected '.'\n", k);
            return;
        }
    }

    if (strchr(str2, figure[k]) == NULL)
    {
        printf("Error at column %d: unexpected character\n", k);
        return;
    }

    while (strchr(str2, figure[k]) != NULL)
    {
        k++;
    }

    if (figure[k] != ')')
    {
        printf("Error at column %d: expected ')'\n", k);
    }
    else
    {
        printf("succeed\n");
    }
}


int main()
{
    printf("Enter number of figures\n");
    int n;
    scanf("%d",&n);
    char figure[64];

    fgets(figure, 64, stdin);

    while (n > 0)
    {
        fgets(figure, 64, stdin);

        figure[0] = tolower(figure[0]);

        switch (figure[0])
        {
        case 'c':
            circle(figure);
            break;
        default:
            printf("Error at column 0: expected 'Circle' or 'Triangle'");
            break;
        }
        n--;
    }

    return 0;
}
