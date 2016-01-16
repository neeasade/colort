#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i=0;
    char *limit;
    char *limitCompare;
    int index = 0;
    int tintValue = 0;
    int original = 0;
    char *colorValues="0123456789abcdef";
    char *colorString;


    // -l (limit), -t (tint value), -c (color string)
    while ((i = getopt  (argc, argv, "lt:c:")) != -1)
        switch(i)
        {
            case 'l':
                limit = optarg; break;
            case 't':
                tintValue = atoi(optarg); break;
            case 'c':
                colorString = optarg; break;
            default:
                abort();
        }

    for (i = 0; colorString[i] != 0; i++)
    {
        switch(colorString[i])
        {
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9': index = colorString[i] - '0'; break;

            case 'a':
            case 'A': index = 10; break;

            case 'b':
            case 'B': index = 11; break;

            case 'c':
            case 'C': index = 12; break;

            case 'd':
            case 'D': index = 13; break;

            case 'e':
            case 'E': index = 14; break;

            case 'f':
            case 'F': index = 15; break;

            default: index = -1; break;
        }

        original = index;
        if (index != -1)
        {
            index += tintValue;

            while(index < 0)
                index += 16;

            index = index % 16;

            /*
            strcpy(limitCompare, "--upper");
            if(strcmp(limit, limitCompare) == 0 && index > original)
                index = 15;

            strcpy(limitCompare, "--lower");
            if(strcmp(limit, limitCompare) == 0 && original > index)
                index = 0;
            */

            colorString[i] = colorValues[index];
        }
    }

    printf("%s\n", colorString);
    return 0;
}
