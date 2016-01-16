#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i=0;
    char limit[20];
    char limitCompare[20];
    int index;
    int original;
    char *colorValues="0123456789abcdef";

    // Args.
    if (argc == 4)
        strcpy(limit, argv[++i]);

    int changeValue = atoi(argv[++i]); // value to change color value by.
    char *color = argv[++i];

    for (i = 0; color[i] != 0; i++)
    {
        switch(color[i])
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
            case '9': index = color[i] - '0'; break;

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
        if ( index != -1 )
        {
            index += changeValue;

            while(index < 0)
                index += 16;

            index=index%16;

            strcpy(limitCompare, "--upper");
            if(strcmp(limit, limitCompare) == 0 && index > original)
                index = 15;

            strcpy(limitCompare, "--lower");
            if(strcmp(limit, limitCompare) == 0 && original > index)
                index = 0;

            color[i] = colorValues[index];
        }
    }

    printf("%s\n",color);
    return 0;
}
